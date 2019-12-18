#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_ota_select_entry_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 int FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ bootloader_flash_erase_sector (int) ; 
 scalar_t__ bootloader_flash_write (int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static esp_err_t write_otadata(esp_ota_select_entry_t *otadata, uint32_t offset, bool write_encrypted)
{
    esp_err_t err = bootloader_flash_erase_sector(offset / FLASH_SECTOR_SIZE);
    if (err == ESP_OK) {
        err = bootloader_flash_write(offset, otadata, sizeof(esp_ota_select_entry_t), write_encrypted);
    }
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error in write_otadata operation. err = 0x%x", err);
    }
    return err;
}