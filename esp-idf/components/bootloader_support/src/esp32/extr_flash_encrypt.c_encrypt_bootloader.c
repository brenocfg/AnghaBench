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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BOOTLOADER_OFFSET ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  FLASH_OFFS_SECURE_BOOT_IV_DIGEST ; 
 int /*<<< orphan*/  FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_flash_encrypt_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_image_verify_bootloader (int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t encrypt_bootloader(void)
{
    esp_err_t err;
    uint32_t image_length;
    /* Check for plaintext bootloader (verification will fail if it's already encrypted) */
    if (esp_image_verify_bootloader(&image_length) == ESP_OK) {
        ESP_LOGD(TAG, "bootloader is plaintext. Encrypting...");
        err = esp_flash_encrypt_region(ESP_BOOTLOADER_OFFSET, image_length);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to encrypt bootloader in place: 0x%x", err);
            return err;
        }

#ifdef CONFIG_SECURE_BOOT_ENABLED
        /* If secure boot is enabled and bootloader was plaintext, also
         * need to encrypt secure boot IV+digest.
         */
        ESP_LOGD(TAG, "Encrypting secure bootloader IV & digest...");
        err = esp_flash_encrypt_region(FLASH_OFFS_SECURE_BOOT_IV_DIGEST,
                                       FLASH_SECTOR_SIZE);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to encrypt bootloader IV & digest in place: 0x%x", err);
            return err;
        }
#endif
    }
    else {
        ESP_LOGW(TAG, "no valid bootloader was found");
    }

    return ESP_OK;
}