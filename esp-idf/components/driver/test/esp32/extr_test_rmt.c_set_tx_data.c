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
 int build_items (int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void set_tx_data(int tx_channel, uint16_t cmd, uint16_t addr, int item_num, rmt_item32_t* item, int offset)
{
    while(1) {
        int i = build_items(tx_channel, item + offset, item_num - offset, ((~addr) << 8) | addr, cmd);
        printf("cmd :%d\n", cmd);
        if(i < 0) {
            break;
        }
        cmd++;
        addr++;
        offset += i;
    }
}