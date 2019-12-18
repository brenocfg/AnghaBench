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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t esp_efuse_block_t ;
struct TYPE_2__ {int end; int start; } ;

/* Variables and functions */
 size_t EFUSE_BLK_MAX ; 
 int /*<<< orphan*/  REG_READ (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* range_read_addr_blocks ; 
 int /*<<< orphan*/ ** virt_blocks ; 

uint32_t esp_efuse_utility_read_reg(esp_efuse_block_t blk, unsigned int num_reg)
{
    assert(blk >= 0 && blk < EFUSE_BLK_MAX);
    unsigned int max_num_reg = (range_read_addr_blocks[blk].end - range_read_addr_blocks[blk].start) / sizeof(uint32_t);
    assert(num_reg <= max_num_reg);
    uint32_t value;
#ifdef CONFIG_EFUSE_VIRTUAL
    value = virt_blocks[blk][num_reg];
#else
    value = REG_READ(range_read_addr_blocks[blk].start + num_reg * 4);
#endif
    return value;
}