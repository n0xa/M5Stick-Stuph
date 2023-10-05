#include <M5StickCPlus.h>
#include "SD.h"

/* 
SD Card Reader Pin Connection Table:
StickCPlus Header - SPI SD Card
            3v3   -   3v3
            GND   -   GND 
             G0   -   CLK
        G36/G25   -   MISO
            G26   -   MOSI
                  -   CS (jumper to SD Card GND Pin)  

Credit: https://lang-ship.com/reference/unofficial/M5StickC/Device/SPI/SD/
*/

SPIClass SPI_EXT;
enum { spi_sck = 0, spi_miso = 36, spi_mosi = 26, spi_ss = -1 };

void setup()
{
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(ORANGE, BLACK);

  SPI_EXT.begin(spi_sck, spi_miso, spi_mosi, spi_ss);

  if (!SD.begin(spi_ss, SPI_EXT)) {
    M5.Lcd.println("Card Mount Failed");
    return;
  }

  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    M5.Lcd.println("No SD Card");
    return;
  }

  M5.Lcd.print("Card Type: ");
  if (cardType == CARD_MMC) {
    M5.Lcd.println("MMC");
  } else if (cardType == CARD_SD) {
    M5.Lcd.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    M5.Lcd.println("SDHC");
  } else {
    M5.Lcd.println("UNKNOWN");
  }
  
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  M5.Lcd.printf("Card Size: %lluMB\n", cardSize);
}

void loop() {
}
