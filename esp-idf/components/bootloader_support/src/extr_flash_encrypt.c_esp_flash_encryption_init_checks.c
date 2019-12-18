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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ esp_flash_enc_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_EARLY_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_EARLY_LOGW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_EFUSE_WR_DIS_FLASH_CRYPT_CNT ; 
 scalar_t__ ESP_FLASH_ENC_MODE_DEVELOPMENT ; 
 scalar_t__ ESP_FLASH_ENC_MODE_RELEASE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ esp_flash_encryption_enabled () ; 
 int /*<<< orphan*/  esp_flash_write_protect_crypt_cnt () ; 
 scalar_t__ esp_get_flash_encryption_mode () ; 
 scalar_t__ esp_secure_boot_enabled () ; 

void esp_flash_encryption_init_checks()
{
    esp_flash_enc_mode_t mode;

    // First check is: if Release mode flash encryption & secure boot are enabled then
    // FLASH_CRYPT_CNT *must* be write protected. This will have happened automatically
    // if bootloader is IDF V4.0 or newer but may not have happened for previous ESP-IDF bootloaders.
#ifdef CONFIG_SECURE_FLASH_ENCRYPTION_MODE_RELEASE
#ifdef CONFIG_SECURE_BOOT_ENABLED
    if (esp_secure_boot_enabled() && esp_flash_encryption_enabled()) {
        uint8_t flash_crypt_cnt_wr_dis = 0;
        esp_efuse_read_field_blob(ESP_EFUSE_WR_DIS_FLASH_CRYPT_CNT, &flash_crypt_cnt_wr_dis, 1);
        if (!flash_crypt_cnt_wr_dis) {
            ESP_EARLY_LOGE(TAG, "Flash encryption & Secure Boot together requires FLASH_CRYPT_CNT efuse to be write protected. Fixing now...");
            esp_flash_write_protect_crypt_cnt();
        }
    }
#endif // CONFIG_SECURE_BOOT_ENABLED
#endif // CONFIG_SECURE_FLASH_ENCRYPTION_MODE_RELEASE

    // Second check is to print a warning or error if the current running flash encryption mode
    // doesn't match the expectation from project config (due to mismatched bootloader and app, probably)
    mode = esp_get_flash_encryption_mode();
    if (mode == ESP_FLASH_ENC_MODE_DEVELOPMENT) {
#ifdef CONFIG_SECURE_FLASH_ENCRYPTION_MODE_RELEASE
        ESP_EARLY_LOGE(TAG, "Flash encryption settings error: app is configured for RELEASE but efuses are set for DEVELOPMENT");
        ESP_EARLY_LOGE(TAG, "Mismatch found in security options in bootloader menuconfig and efuse settings. Device is not secure.");
#else
        ESP_EARLY_LOGW(TAG, "Flash encryption mode is DEVELOPMENT (not secure)");
#endif
    } else if (mode == ESP_FLASH_ENC_MODE_RELEASE) {
        ESP_EARLY_LOGI(TAG, "Flash encryption mode is RELEASE");
    }
}