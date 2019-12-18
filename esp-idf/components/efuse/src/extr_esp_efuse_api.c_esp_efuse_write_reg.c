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
typedef  int /*<<< orphan*/  esp_efuse_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_LOCK_ACQUIRE_RUCURSIVE () ; 
 int /*<<< orphan*/  EFUSE_LOCK_RELEASE_RUCURSIVE () ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_efuse_utility_apply_new_coding_scheme () ; 
 int /*<<< orphan*/  esp_efuse_utility_burn_efuses () ; 
 int /*<<< orphan*/  esp_efuse_utility_reset () ; 
 scalar_t__ esp_efuse_utility_write_reg (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int s_batch_writing_mode ; 

esp_err_t esp_efuse_write_reg(esp_efuse_block_t blk, unsigned int num_reg, uint32_t val)
{
    EFUSE_LOCK_ACQUIRE_RUCURSIVE();
    if (s_batch_writing_mode == false) {
        esp_efuse_utility_reset();
    }
    esp_err_t err = esp_efuse_utility_write_reg(blk, num_reg, val);
    if (s_batch_writing_mode == false) {
        if (err == ESP_OK) {
            err = esp_efuse_utility_apply_new_coding_scheme();
            if (err == ESP_OK) {
                esp_efuse_utility_burn_efuses();
            }
        }
        esp_efuse_utility_reset();
    }
    EFUSE_LOCK_RELEASE_RUCURSIVE();
    return err;
}