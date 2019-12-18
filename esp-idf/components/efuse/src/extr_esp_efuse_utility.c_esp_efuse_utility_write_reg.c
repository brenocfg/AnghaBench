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
typedef  int /*<<< orphan*/  esp_efuse_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_EFUSE_REPEATED_PROG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int esp_efuse_utility_read_reg (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,unsigned int,int) ; 

esp_err_t esp_efuse_utility_write_reg(esp_efuse_block_t efuse_block, unsigned int num_reg, uint32_t reg_to_write)
{
    esp_err_t err = ESP_OK;
    uint32_t reg = esp_efuse_utility_read_reg(efuse_block, num_reg);
    if (reg & reg_to_write) {
        ESP_LOGE(TAG, "Repeated programming of programmed bits is strictly forbidden 0x%08x", reg & reg_to_write);
        err = ESP_ERR_EFUSE_REPEATED_PROG;
    } else {
        write_reg(efuse_block, num_reg, reg_to_write);
    }
    return err;
}