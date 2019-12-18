#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int spi_size; } ;
typedef  TYPE_1__ esp_image_header_t ;
struct TYPE_5__ {int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cache_Flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cache_Read_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cache_Read_Enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cache_Resume_ICache (int) ; 
 int Cache_Suspend_ICache () ; 
#define  ESP_IMAGE_FLASH_SIZE_16MB 132 
#define  ESP_IMAGE_FLASH_SIZE_1MB 131 
#define  ESP_IMAGE_FLASH_SIZE_2MB 130 
#define  ESP_IMAGE_FLASH_SIZE_4MB 129 
#define  ESP_IMAGE_FLASH_SIZE_8MB 128 
 int /*<<< orphan*/  esp_rom_spiflash_config_param (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 TYPE_3__ g_rom_flashchip ; 

__attribute__((used)) static void update_flash_config(const esp_image_header_t *pfhdr)
{
    uint32_t size;
    switch (pfhdr->spi_size) {
    case ESP_IMAGE_FLASH_SIZE_1MB:
        size = 1;
        break;
    case ESP_IMAGE_FLASH_SIZE_2MB:
        size = 2;
        break;
    case ESP_IMAGE_FLASH_SIZE_4MB:
        size = 4;
        break;
    case ESP_IMAGE_FLASH_SIZE_8MB:
        size = 8;
        break;
    case ESP_IMAGE_FLASH_SIZE_16MB:
        size = 16;
        break;
    default:
        size = 2;
    }
#if CONFIG_IDF_TARGET_ESP32
    Cache_Read_Disable(0);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    uint32_t autoload = Cache_Suspend_ICache();
#endif
    // Set flash chip size
    esp_rom_spiflash_config_param(g_rom_flashchip.device_id, size * 0x100000, 0x10000, 0x1000, 0x100, 0xffff);
    // TODO: set mode
    // TODO: set frequency
#if CONFIG_IDF_TARGET_ESP32
    Cache_Flush(0);
    Cache_Read_Enable(0);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    Cache_Resume_ICache(autoload);
#endif
}