/*!
 * @file Adafruit_FT6206.h
 */

#ifndef ADAFRUIT_FT6206_LIBRARY
#define ADAFRUIT_FT6206_LIBRARY

#include "Arduino.h"
#include <Wire.h>

#define FT62XX_ADDR 0x38           //!< I2C address
#define FT62XX_G_FT5201ID 0xA8     //!< FocalTech's panel ID
#define FT62XX_REG_NUMTOUCHES 0x02 //!< Number of touch points

#define FT62XX_NUM_X 0x33 //!< Touch X position
#define FT62XX_NUM_Y 0x34 //!< Touch Y position

#define FT62XX_REG_MODE 0x00        //!< Device mode, either WORKING or FACTORY
#define FT62XX_REG_CALIBRATE 0x02   //!< Calibrate mode
#define FT62XX_REG_WORKMODE 0x00    //!< Work mode
#define FT62XX_REG_FACTORYMODE 0x40 //!< Factory mode
#define FT62XX_REG_THRESHHOLD 0x80  //!< Threshold for touch detection
#define FT62XX_REG_POINTRATE 0x88   //!< Point rate
#define FT62XX_REG_FIRMVERS 0xA6    //!< Firmware version
#define FT62XX_REG_CHIPID 0xA3      //!< Chip selecting
#define FT62XX_REG_VENDID 0xA8      //!< FocalTech's panel ID

#define FT62XX_VENDID 0x11  //!< FocalTech's panel ID
#define FT6206_CHIPID 0x06  //!< Chip selecting
#define FT6236_CHIPID 0x36  //!< Chip selecting
#define FT6236U_CHIPID 0x64 //!< Chip selecting

/*
enum gest{
  GEST_UP =       0x10,
  GEST_RIGHT =    0x14,
  GEST_DOWN =     0x18,
  GEST_LEFT =     0x1c,
  GEST_ZOOM_IN =  0x48,
  GEST_ZOOM_OUT = 0x49,
  GEST_NONE =     0x00
}
*/

// calibrated for Adafruit 2.8" ctp screen
#define FT62XX_DEFAULT_THRESHOLD 128 //!< Default threshold for touch detection

/**************************************************************************/
/*!
    @brief  Helper class that stores a TouchScreen Point with x, y, and z
   coordinates, for easy math/comparison
*/
/**************************************************************************/
class TS_Point {
public:
  TS_Point(void);
  TS_Point(int16_t x, int16_t y, int16_t z, uint8_t gesture);
  

  bool operator==(TS_Point);
  bool operator!=(TS_Point);

  int16_t x; /*!< X coordinate */
  int16_t y; /*!< Y coordinate */
  int16_t z; /*!< Z coordinate (often used for pressure) */
  //gest gesture;
  uint8_t gesture;
};

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with FT6206
   capacitive touch chips
*/
/**************************************************************************/
class Adafruit_FT6206 {
public:
  Adafruit_FT6206(int8_t intPin = -1, int8_t rstPin = -1);
  boolean begin(uint8_t thresh = FT62XX_DEFAULT_THRESHOLD);
  uint8_t touched(void);
  bool touchedInt(void);
  TS_Point getPoint(uint8_t n = 0);

  // void autoCalibrate(void);

private:
  void writeRegister8(uint8_t reg, uint8_t val);
  uint8_t readRegister8(uint8_t reg);

  void readData(void);
  uint8_t touches;
  uint16_t touchX[2], touchY[2], touchID[2];
  uint8_t touchGesture;
  int8_t rstPin;
  int8_t intPin;
};

#endif // ADAFRUIT_FT6206_LIBRARY
