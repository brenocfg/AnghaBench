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
typedef  int esp_err_t ;

/* Variables and functions */
 int ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int ESP_OK ; 
 int FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 int bootloader_flash_erase_sector (int) ; 
 int bootloader_flash_read (int,int*,int,int) ; 
 int bootloader_flash_write (int,int*,int,int) ; 

esp_err_t esp_flash_encrypt_region(uint32_t src_addr, size_t data_length)
{
    esp_err_t err;
    uint32_t buf[FLASH_SECTOR_SIZE / sizeof(uint32_t)];

    if (src_addr % FLASH_SECTOR_SIZE != 0) {
        ESP_LOGE(TAG, "esp_flash_encrypt_region bad src_addr 0x%x",src_addr);
        return ESP_FAIL;
    }

    for (size_t i = 0; i < data_length; i += FLASH_SECTOR_SIZE) {
        uint32_t sec_start = i + src_addr;
        err = bootloader_flash_read(sec_start, buf, FLASH_SECTOR_SIZE, false);
        if (err != ESP_OK) {
            goto flash_failed;
        }
        err = bootloader_flash_erase_sector(sec_start / FLASH_SECTOR_SIZE);
        if (err != ESP_OK) {
            goto flash_failed;
        }
        err = bootloader_flash_write(sec_start, buf, FLASH_SECTOR_SIZE, true);
        if (err != ESP_OK) {
            goto flash_failed;
        }
    }
    return ESP_OK;

 flash_failed:
    ESP_LOGE(TAG, "flash operation failed: 0x%x", err);
    return err;
}