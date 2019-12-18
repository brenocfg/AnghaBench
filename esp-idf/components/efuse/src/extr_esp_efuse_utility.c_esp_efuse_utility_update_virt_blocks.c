#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int COUNT_EFUSE_BLOCKS ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* range_read_addr_blocks ; 
 int /*<<< orphan*/ ** virt_blocks ; 

void esp_efuse_utility_update_virt_blocks(void)
{
#ifdef CONFIG_EFUSE_VIRTUAL
    ESP_LOGI(TAG, "Loading virtual efuse blocks from real efuses");
    for (int num_block = 0; num_block < COUNT_EFUSE_BLOCKS; num_block++) {
        int subblock = 0;
        for (uint32_t addr_rd_block = range_read_addr_blocks[num_block].start; addr_rd_block <= range_read_addr_blocks[num_block].end; addr_rd_block += 4) {
            virt_blocks[num_block][subblock++] = REG_READ(addr_rd_block);
        }
        ESP_LOGD(TAG, "virt_blocks[%d] is filled by EFUSE_BLOCK%d", num_block, num_block);
    }
#else
    ESP_LOGI(TAG, "Emulate efuse is disabled");
#endif
}