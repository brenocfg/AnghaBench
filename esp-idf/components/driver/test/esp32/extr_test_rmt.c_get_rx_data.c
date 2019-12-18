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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  rmt_item32_t ;
typedef  scalar_t__ RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int parse_items (int /*<<< orphan*/ *,size_t,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  vRingbufferReturnItem (scalar_t__,void*) ; 
 scalar_t__ xRingbufferReceive (scalar_t__,size_t*,int) ; 

__attribute__((used)) static int get_rx_data(RingbufHandle_t rb)
{
    uint16_t tmp = 0;
    while(rb) {
        size_t rx_size = 0;
        rmt_item32_t* rx_item = (rmt_item32_t*) xRingbufferReceive(rb, &rx_size, 1000);
        if(rx_item) {
            uint16_t rmt_addr;
            uint16_t rmt_cmd;
            int rx_offset = 0;
            while(1) {
                int res = parse_items(rx_item + rx_offset, rx_size / 4 - rx_offset, &rmt_addr, &rmt_cmd);
                if(res > 0) {
                    rx_offset += res + 1;
                    ESP_LOGI(TAG, "RMT RCV --- addr: 0x%04x cmd: 0x%04x", rmt_addr, rmt_cmd);
                    TEST_ASSERT(rmt_cmd == tmp);
                    tmp++;
                } else {
                    break;
                }
            }
            vRingbufferReturnItem(rb, (void*) rx_item);
        } else {
            break;
        }
    }
    return tmp;
}