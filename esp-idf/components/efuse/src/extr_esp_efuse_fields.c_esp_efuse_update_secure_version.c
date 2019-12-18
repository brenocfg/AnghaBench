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
typedef  unsigned long long uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ esp_efuse_coding_scheme_t ;

/* Variables and functions */
 unsigned long long CONFIG_BOOTLOADER_APP_SEC_VER_SIZE_EFUSE_FIELD ; 
 scalar_t__ EFUSE_CODING_SCHEME_NONE ; 
 int /*<<< orphan*/  ESP_EFUSE_SECURE_VERSION_NUM_BLOCK ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_efuse_get_coding_scheme (int /*<<< orphan*/ ) ; 
 unsigned long long esp_efuse_read_secure_version () ; 
 int /*<<< orphan*/  write_anti_rollback (unsigned long long) ; 

esp_err_t esp_efuse_update_secure_version(uint32_t secure_version)
{
#ifdef CONFIG_BOOTLOADER_APP_ANTI_ROLLBACK
    if (CONFIG_BOOTLOADER_APP_SEC_VER_SIZE_EFUSE_FIELD < secure_version) {
        ESP_LOGE(TAG, "Max secure version is %d. Given %d version can not be written.", CONFIG_BOOTLOADER_APP_SEC_VER_SIZE_EFUSE_FIELD, secure_version);
        return ESP_ERR_INVALID_ARG;
    }
#ifndef CONFIG_BOOTLOADER_EFUSE_SECURE_VERSION_EMULATE
    esp_efuse_coding_scheme_t coding_scheme = esp_efuse_get_coding_scheme(ESP_EFUSE_SECURE_VERSION_NUM_BLOCK);
    if (coding_scheme != EFUSE_CODING_SCHEME_NONE) {
        ESP_LOGE(TAG, "Anti rollback is not supported with any coding scheme.");
        return ESP_ERR_NOT_SUPPORTED;
    }
#endif
    uint32_t sec_ver_hw = esp_efuse_read_secure_version();
    // If secure_version is the same as in eFuse field than it is ok just go out.
    if (sec_ver_hw < secure_version) {
        uint32_t num_bit_hw = (1ULL << sec_ver_hw) - 1;
        uint32_t num_bit_app = (1ULL << secure_version) - 1;
        // Repeated programming of programmed bits is strictly forbidden
        uint32_t new_bits = num_bit_app - num_bit_hw; // get only new bits
        write_anti_rollback(new_bits);
        ESP_LOGI(TAG, "Anti-rollback is set. eFuse field is updated(%d).", secure_version);
    } else if (sec_ver_hw > secure_version) {
        ESP_LOGE(TAG, "Anti-rollback is not set. secure_version of app is lower that eFuse field(%d).", sec_ver_hw);
        return ESP_FAIL;
    }
#endif
    return ESP_OK;
}