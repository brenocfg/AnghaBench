#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int COUNT_EFUSE_BLOCKS ; 
 scalar_t__ EFUSE_CODING_SCHEME_RS ; 
 int /*<<< orphan*/  ESP_ERR_CODING ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_efuse_get_coding_scheme (int) ; 
 scalar_t__ esp_efuse_utility_read_reg (int,int) ; 
 TYPE_2__* range_read_addr_blocks ; 
 TYPE_1__* range_write_addr_blocks ; 

esp_err_t esp_efuse_utility_apply_new_coding_scheme()
{
    // start with EFUSE_BLK1. EFUSE_BLK0 - always uses EFUSE_CODING_SCHEME_NONE.
    for (int num_block = 1; num_block < COUNT_EFUSE_BLOCKS; num_block++) {
        if (esp_efuse_get_coding_scheme(num_block) == EFUSE_CODING_SCHEME_RS) {
            for (uint32_t addr_wr_block = range_write_addr_blocks[num_block].start; addr_wr_block <= range_write_addr_blocks[num_block].end; addr_wr_block += 4) {
                if (REG_READ(addr_wr_block)) {
                    int num_reg = 0;
                    for (uint32_t addr_rd_block = range_read_addr_blocks[num_block].start; addr_rd_block <= range_read_addr_blocks[num_block].end; addr_rd_block += 4, ++num_reg) {
                        if (esp_efuse_utility_read_reg(num_block, num_reg)) {
                        	ESP_LOGE(TAG, "Bits are not empty. Write operation is forbidden.");
                            return ESP_ERR_CODING;
                        }
                    }
                    break;
                }
            }
        }
    }
    return ESP_OK;
}