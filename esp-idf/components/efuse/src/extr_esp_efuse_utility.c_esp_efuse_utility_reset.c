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
 int /*<<< orphan*/  REG_WRITE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_efuse_utility_clear_program_registers () ; 
 TYPE_1__* range_write_addr_blocks ; 

void esp_efuse_utility_reset(void)
{
    esp_efuse_utility_clear_program_registers();
    for (int num_block = 0; num_block < COUNT_EFUSE_BLOCKS; num_block++) {
        for (uint32_t addr_wr_block = range_write_addr_blocks[num_block].start; addr_wr_block <= range_write_addr_blocks[num_block].end; addr_wr_block += 4) {
            REG_WRITE(addr_wr_block, 0);
        }
    }
}