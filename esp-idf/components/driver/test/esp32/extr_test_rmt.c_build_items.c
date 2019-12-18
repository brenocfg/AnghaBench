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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  rmt_item32_t ;

/* Variables and functions */
 int DATA_ITEM_NUM ; 
 int /*<<< orphan*/  fill_item_bit_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_item_bit_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_item_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_item_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_items(int channel, rmt_item32_t* item, int item_num, uint16_t addr, uint16_t cmd_data)
{
    int i = 0, j = 0;
    if(item_num < DATA_ITEM_NUM) {
        return -1;
    }
    fill_item_header(item++);
    i++;
    for(j = 0; j < 16; j++) {
        if(addr & 0x1) {
            fill_item_bit_one(item);
        } else {
            fill_item_bit_zero(item);
        }
        item++;
        i++;
        addr >>= 1;
    }
    for(j = 0; j < 16; j++) {
        if(cmd_data & 0x1) {
            fill_item_bit_one(item);
        } else {
            fill_item_bit_zero(item);
        }
        item++;
        i++;
        cmd_data >>= 1;
    }
    fill_item_end(item);
    i++;
    return i;
}