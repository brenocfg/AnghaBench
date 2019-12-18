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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_BLK0_RDATA0_REG ; 
 int /*<<< orphan*/  EFUSE_BLK0_RDATA6_REG ; 
 int /*<<< orphan*/  EFUSE_BLK0_WDATA0_REG ; 
 int /*<<< orphan*/  EFUSE_BLK0_WDATA6_REG ; 
 int EFUSE_RD_ABS_DONE_0 ; 
 int EFUSE_RD_CONSOLE_DEBUG_DISABLE ; 
 int EFUSE_RD_DISABLE_JTAG ; 
 int EFUSE_RD_DIS_BLK2 ; 
 int EFUSE_WR_DIS_BLK2 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  burn_efuses () ; 
 scalar_t__ esp_secure_boot_enabled () ; 

esp_err_t esp_secure_boot_permanently_enable(void)
{
    if (esp_secure_boot_enabled()) {
        ESP_LOGI(TAG, "bootloader secure boot is already enabled, continuing..");
        return ESP_OK;
    }

    uint32_t dis_reg = REG_READ(EFUSE_BLK0_RDATA0_REG);
    bool efuse_key_read_protected = dis_reg & EFUSE_RD_DIS_BLK2;
    bool efuse_key_write_protected = dis_reg & EFUSE_WR_DIS_BLK2;
    if (efuse_key_read_protected == false
        && efuse_key_write_protected == false) {
        ESP_LOGI(TAG, "Read & write protecting new key...");
        REG_WRITE(EFUSE_BLK0_WDATA0_REG, EFUSE_WR_DIS_BLK2 | EFUSE_RD_DIS_BLK2);
        burn_efuses();
        efuse_key_read_protected = true;
        efuse_key_write_protected = true;
    }

    if (!efuse_key_read_protected) {
        ESP_LOGE(TAG, "Pre-loaded key is not read protected. Refusing to blow secure boot efuse.");
        return ESP_ERR_INVALID_STATE;
    }
    if (!efuse_key_write_protected) {
        ESP_LOGE(TAG, "Pre-loaded key is not write protected. Refusing to blow secure boot efuse.");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "blowing secure boot efuse...");
    ESP_LOGD(TAG, "before updating, EFUSE_BLK0_RDATA6 %x", REG_READ(EFUSE_BLK0_RDATA6_REG));

    uint32_t new_wdata6 = EFUSE_RD_ABS_DONE_0;

#ifndef CONFIG_SECURE_BOOT_ALLOW_JTAG
    ESP_LOGI(TAG, "Disable JTAG...");
    new_wdata6 |= EFUSE_RD_DISABLE_JTAG;
#else
    ESP_LOGW(TAG, "Not disabling JTAG - SECURITY COMPROMISED");
#endif

#ifndef CONFIG_SECURE_BOOT_ALLOW_ROM_BASIC
    ESP_LOGI(TAG, "Disable ROM BASIC interpreter fallback...");
    new_wdata6 |= EFUSE_RD_CONSOLE_DEBUG_DISABLE;
#else
    ESP_LOGW(TAG, "Not disabling ROM BASIC fallback - SECURITY COMPROMISED");
#endif

    REG_WRITE(EFUSE_BLK0_WDATA6_REG, new_wdata6);
    burn_efuses();
    uint32_t after = REG_READ(EFUSE_BLK0_RDATA6_REG);
    ESP_LOGD(TAG, "after updating, EFUSE_BLK0_RDATA6 %x", after);
    if (after & EFUSE_RD_ABS_DONE_0) {
        ESP_LOGI(TAG, "secure boot is now enabled for bootloader image");
        return ESP_OK;
    } else {
        ESP_LOGE(TAG, "secure boot not enabled for bootloader image, EFUSE_RD_ABS_DONE_0 is probably write protected!");
        return ESP_ERR_INVALID_STATE;
    }
}