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
 scalar_t__ bit_one_if (int /*<<< orphan*/ *) ; 
 scalar_t__ bit_zero_if (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  header_if (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_items(rmt_item32_t* item, int item_num, uint16_t* addr, uint16_t* data)
{
    int w_len = item_num;
    if(w_len < DATA_ITEM_NUM) {
        return -1;
    }
    int i = 0, j = 0;
    if(!header_if(item++)) {
        return -1;
    }
    uint16_t addr_t = 0;
    for(j = 0; j < 16; j++) {
        if(bit_one_if(item)) {
            addr_t |= (1 << j);
        } else if(bit_zero_if(item)) {
            addr_t |= (0 << j);
        } else {
            return -1;
        }
        item++;
        i++;
    }
    uint16_t data_t = 0;
    for(j = 0; j < 16; j++) {
        if(bit_one_if(item)) {
            data_t |= (1 << j);
        } else if(bit_zero_if(item)) {
            data_t |= (0 << j);
        } else {
            return -1;
        }
        item++;
        i++;
    }
    *addr = addr_t;
    *data = data_t;
    return i;
}