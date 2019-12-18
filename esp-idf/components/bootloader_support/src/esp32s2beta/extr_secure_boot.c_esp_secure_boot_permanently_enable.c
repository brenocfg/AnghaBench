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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_PGM_DATA3_REG ; 
 int /*<<< orphan*/  EFUSE_SECURE_BOOT_EN ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  ETS_EFUSE_BLOCK0 ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  ets_efuse_clear_program_registers () ; 
 int /*<<< orphan*/  ets_efuse_program (int /*<<< orphan*/ ) ; 
 scalar_t__ ets_efuse_secure_boot_enabled () ; 
 int ets_secure_boot_verify_bootloader (int /*<<< orphan*/ *,int) ; 

esp_err_t esp_secure_boot_permanently_enable(void)
{
    uint8_t hash[32];

    if (ets_efuse_secure_boot_enabled())
    {
        ESP_LOGI(TAG, "secure boot is already enabled, continuing..");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "Verifying bootloader signature...\n");
    int r = ets_secure_boot_verify_bootloader(hash, false);
    if (r != ESP_OK) {
        ESP_LOGE(TAG, "Failed to verify bootloader signature");
        return r;
    }

    ets_efuse_clear_program_registers();
    REG_SET_BIT(EFUSE_PGM_DATA3_REG, EFUSE_SECURE_BOOT_EN);
    ets_efuse_program(ETS_EFUSE_BLOCK0);

    assert(ets_efuse_secure_boot_enabled());
    ESP_LOGI(TAG, "Secure boot permanently enabled");

    return ESP_OK;
}