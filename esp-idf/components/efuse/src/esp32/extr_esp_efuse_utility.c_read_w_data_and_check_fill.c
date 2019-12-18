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
typedef  size_t esp_efuse_block_t ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  REG_WRITE (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* range_write_addr_blocks ; 

__attribute__((used)) static bool read_w_data_and_check_fill(esp_efuse_block_t num_block, uint32_t *buf_w_data)
{
    bool blk_is_filled = false;
    int i = 0;
    for (uint32_t addr_wr_block = range_write_addr_blocks[num_block].start; addr_wr_block <= range_write_addr_blocks[num_block].end; addr_wr_block += 4, ++i) {
        buf_w_data[i] = REG_READ(addr_wr_block);
        if (buf_w_data[i] != 0) {
            REG_WRITE(addr_wr_block, 0);
            blk_is_filled = true;
        }
    }
    return blk_is_filled;
}