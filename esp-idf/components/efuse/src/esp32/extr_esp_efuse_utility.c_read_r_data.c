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
 scalar_t__ esp_efuse_utility_read_reg (size_t,int) ; 
 TYPE_1__* range_read_addr_blocks ; 

__attribute__((used)) static void read_r_data(esp_efuse_block_t num_block, uint32_t* buf_r_data)
{
    int i = 0;
    for (uint32_t addr_rd_block = range_read_addr_blocks[num_block].start; addr_rd_block <= range_read_addr_blocks[num_block].end; addr_rd_block += 4, ++i) {
        buf_r_data[i] = esp_efuse_utility_read_reg(num_block, i);
    }
}