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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  rmt_item32_t ;
typedef  int /*<<< orphan*/ * RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEC_TAG ; 
 int RMT_RX_CHANNEL ; 
 int nec_parse_items (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nec_rx_init () ; 
 int /*<<< orphan*/  rmt_get_ringbuf_handle (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  rmt_rx_start (int,int) ; 
 int /*<<< orphan*/  vRingbufferReturnItem (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ xRingbufferReceive (int /*<<< orphan*/ *,size_t*,int) ; 

__attribute__((used)) static void rmt_example_nec_rx_task(void *arg)
{
    int channel = RMT_RX_CHANNEL;
    nec_rx_init();
    RingbufHandle_t rb = NULL;
    //get RMT RX ringbuffer
    rmt_get_ringbuf_handle(channel, &rb);
    rmt_rx_start(channel, 1);
    while(rb) {
        size_t rx_size = 0;
        //try to receive data from ringbuffer.
        //RMT driver will push all the data it receives to its ringbuffer.
        //We just need to parse the value and return the spaces of ringbuffer.
        rmt_item32_t* item = (rmt_item32_t*) xRingbufferReceive(rb, &rx_size, 1000);
        if(item) {
            uint16_t rmt_addr;
            uint16_t rmt_cmd;
            int offset = 0;
            while(1) {
                //parse data value from ringbuffer.
                int res = nec_parse_items(item + offset, rx_size / 4 - offset, &rmt_addr, &rmt_cmd);
                if(res > 0) {
                    offset += res + 1;
                    ESP_LOGI(NEC_TAG, "RMT RCV --- addr: 0x%04x cmd: 0x%04x", rmt_addr, rmt_cmd);
                } else {
                    break;
                }
            }
            //after parsing the data, return spaces to ringbuffer.
            vRingbufferReturnItem(rb, (void*) item);
        } else {
            break;
        }
    }
    vTaskDelete(NULL);
}