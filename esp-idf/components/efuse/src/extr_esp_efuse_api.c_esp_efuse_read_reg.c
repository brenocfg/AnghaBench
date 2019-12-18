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
typedef  int /*<<< orphan*/  esp_efuse_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_LOCK_ACQUIRE () ; 
 int /*<<< orphan*/  EFUSE_LOCK_RELEASE () ; 
 int /*<<< orphan*/  esp_efuse_utility_read_reg (int /*<<< orphan*/ ,unsigned int) ; 

uint32_t esp_efuse_read_reg(esp_efuse_block_t blk, unsigned int num_reg)
{
    EFUSE_LOCK_ACQUIRE();
    uint32_t ret_val = esp_efuse_utility_read_reg(blk, num_reg);
    EFUSE_LOCK_RELEASE();
    return ret_val;
}