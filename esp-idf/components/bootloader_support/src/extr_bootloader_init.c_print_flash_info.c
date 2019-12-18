#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int magic; int segment_count; int spi_mode; int spi_speed; int spi_size; } ;
typedef  TYPE_1__ esp_image_header_t ;

/* Variables and functions */
#define  ESP_IMAGE_FLASH_SIZE_16MB 136 
#define  ESP_IMAGE_FLASH_SIZE_1MB 135 
#define  ESP_IMAGE_FLASH_SIZE_2MB 134 
#define  ESP_IMAGE_FLASH_SIZE_4MB 133 
#define  ESP_IMAGE_FLASH_SIZE_8MB 132 
#define  ESP_IMAGE_SPI_SPEED_20M 131 
#define  ESP_IMAGE_SPI_SPEED_26M 130 
#define  ESP_IMAGE_SPI_SPEED_40M 129 
#define  ESP_IMAGE_SPI_SPEED_80M 128 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char const*) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CTRL_REG (int /*<<< orphan*/ ) ; 
 int SPI_FASTRD_MODE ; 
 int SPI_FREAD_DIO ; 
 int SPI_FREAD_DUAL ; 
 int SPI_FREAD_QIO ; 
 int SPI_FREAD_QUAD ; 
 int /*<<< orphan*/  SPI_MEM_CTRL_REG (int /*<<< orphan*/ ) ; 
 int SPI_MEM_FASTRD_MODE ; 
 int SPI_MEM_FREAD_DIO ; 
 int SPI_MEM_FREAD_DUAL ; 
 int SPI_MEM_FREAD_QIO ; 
 int SPI_MEM_FREAD_QUAD ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static void print_flash_info(const esp_image_header_t *phdr)
{
#if (BOOT_LOG_LEVEL >= BOOT_LOG_LEVEL_NOTICE)

    ESP_LOGD(TAG, "magic %02x", phdr->magic );
    ESP_LOGD(TAG, "segments %02x", phdr->segment_count );
    ESP_LOGD(TAG, "spi_mode %02x", phdr->spi_mode );
    ESP_LOGD(TAG, "spi_speed %02x", phdr->spi_speed );
    ESP_LOGD(TAG, "spi_size %02x", phdr->spi_size );

    const char *str;
    switch ( phdr->spi_speed ) {
    case ESP_IMAGE_SPI_SPEED_40M:
        str = "40MHz";
        break;
    case ESP_IMAGE_SPI_SPEED_26M:
        str = "26.7MHz";
        break;
    case ESP_IMAGE_SPI_SPEED_20M:
        str = "20MHz";
        break;
    case ESP_IMAGE_SPI_SPEED_80M:
        str = "80MHz";
        break;
    default:
        str = "20MHz";
        break;
    }
    ESP_LOGI(TAG, "SPI Speed      : %s", str );

    /* SPI mode could have been set to QIO during boot already,
       so test the SPI registers not the flash header */
#if CONFIG_IDF_TARGET_ESP32
    uint32_t spi_ctrl = REG_READ(SPI_CTRL_REG(0));
    if (spi_ctrl & SPI_FREAD_QIO) {
        str = "QIO";
    } else if (spi_ctrl & SPI_FREAD_QUAD) {
        str = "QOUT";
    } else if (spi_ctrl & SPI_FREAD_DIO) {
        str = "DIO";
    } else if (spi_ctrl & SPI_FREAD_DUAL) {
        str = "DOUT";
    } else if (spi_ctrl & SPI_FASTRD_MODE) {
        str = "FAST READ";
    } else {
        str = "SLOW READ";
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    uint32_t spi_ctrl = REG_READ(SPI_MEM_CTRL_REG(0));
    if (spi_ctrl & SPI_MEM_FREAD_QIO) {
        str = "QIO";
    } else if (spi_ctrl & SPI_MEM_FREAD_QUAD) {
        str = "QOUT";
    } else if (spi_ctrl & SPI_MEM_FREAD_DIO) {
        str = "DIO";
    } else if (spi_ctrl & SPI_MEM_FREAD_DUAL) {
        str = "DOUT";
    } else if (spi_ctrl & SPI_MEM_FASTRD_MODE) {
        str = "FAST READ";
    } else {
        str = "SLOW READ";
    }
#endif
    ESP_LOGI(TAG, "SPI Mode       : %s", str );

    switch ( phdr->spi_size ) {
    case ESP_IMAGE_FLASH_SIZE_1MB:
        str = "1MB";
        break;
    case ESP_IMAGE_FLASH_SIZE_2MB:
        str = "2MB";
        break;
    case ESP_IMAGE_FLASH_SIZE_4MB:
        str = "4MB";
        break;
    case ESP_IMAGE_FLASH_SIZE_8MB:
        str = "8MB";
        break;
    case ESP_IMAGE_FLASH_SIZE_16MB:
        str = "16MB";
        break;
    default:
        str = "2MB";
        break;
    }
    ESP_LOGI(TAG, "SPI Flash Size : %s", str );
#endif
}