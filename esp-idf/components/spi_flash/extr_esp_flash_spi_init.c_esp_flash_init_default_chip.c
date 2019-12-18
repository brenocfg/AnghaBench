#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  memspi_host_config_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_8__ {int size; TYPE_1__* host; } ;
struct TYPE_7__ {int chip_size; } ;
struct TYPE_6__ {int /*<<< orphan*/ * driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGE (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_EARLY_LOGW (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ ESP_ERR_FLASH_SIZE_NOT_MATCH ; 
 int /*<<< orphan*/  ESP_FLASH_HOST_CONFIG_DEFAULT () ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_3__ default_chip ; 
 int /*<<< orphan*/  default_driver_data ; 
 TYPE_3__* esp_flash_default_chip ; 
 scalar_t__ esp_flash_init (TYPE_3__*) ; 
 TYPE_2__ g_rom_flashchip ; 
 int /*<<< orphan*/  spi_flash_hal_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

esp_err_t esp_flash_init_default_chip(void)
{
    memspi_host_config_t cfg = ESP_FLASH_HOST_CONFIG_DEFAULT();
    //the host is already initialized, only do init for the data and load it to the host
    spi_flash_hal_init(&default_driver_data, &cfg);
    default_chip.host->driver_data = &default_driver_data;

    // ROM TODO: account for non-standard default pins in efuse
    // ROM TODO: to account for chips which are slow to power on, maybe keep probing in a loop here
    esp_err_t err = esp_flash_init(&default_chip);
    if (err != ESP_OK) {
        return err;
    }
    if (default_chip.size < g_rom_flashchip.chip_size) {
        ESP_EARLY_LOGE(TAG, "Detected size(%dk) smaller than the size in the binary image header(%dk). Probe failed.", default_chip.size/1024, g_rom_flashchip.chip_size/1024);
        return ESP_ERR_FLASH_SIZE_NOT_MATCH;
    } else if (default_chip.size > g_rom_flashchip.chip_size) {
        ESP_EARLY_LOGW(TAG, "Detected size(%dk) larger than the size in the binary image header(%dk). Using the size in the binary image header.", default_chip.size/1024, g_rom_flashchip.chip_size/1024);
        default_chip.size = g_rom_flashchip.chip_size;
    }
    default_chip.size = g_rom_flashchip.chip_size;

    esp_flash_default_chip = &default_chip;
    return ESP_OK;
}