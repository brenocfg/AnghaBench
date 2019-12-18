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
 int REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* range_read_addr_blocks ; 
 int** virt_blocks ; 

void esp_efuse_utility_debug_dump_blocks(void)
{
    printf("EFUSE_BLKx:\n");
#ifdef CONFIG_EFUSE_VIRTUAL
    for (int num_block = 0; num_block < COUNT_EFUSE_BLOCKS; num_block++) {
        int num_reg = 0;
        printf("%d) ", num_block);
        for (uint32_t addr_rd_block = range_read_addr_blocks[num_block].start; addr_rd_block <= range_read_addr_blocks[num_block].end; addr_rd_block += 4, num_reg++) {
            printf("0x%08x ", virt_blocks[num_block][num_reg]);
        }
        printf("\n");
    }
#else
    for (int num_block = 0; num_block < COUNT_EFUSE_BLOCKS; num_block++) {
        printf("%d) ", num_block);
        for (uint32_t addr_rd_block = range_read_addr_blocks[num_block].start; addr_rd_block <= range_read_addr_blocks[num_block].end; addr_rd_block += 4) {
            printf("0x%08x ", REG_READ(addr_rd_block));
        }
        printf("\n");
    }
#endif
    printf("\n");
}