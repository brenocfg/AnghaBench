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
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOG_INFO ; 
 int NEC_DATA_ITEM_NUM ; 
 int /*<<< orphan*/  NEC_TAG ; 
 int RMT_TX_CHANNEL ; 
 int RMT_TX_DATA_NUM ; 
 int /*<<< orphan*/  esp_log_level_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int nec_build_items (int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  nec_tx_init () ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  rmt_wait_tx_done (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_write_items (int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rmt_example_nec_tx_task(void *arg)
{
    vTaskDelay(10);
    nec_tx_init();
    esp_log_level_set(NEC_TAG, ESP_LOG_INFO);
    int channel = RMT_TX_CHANNEL;
    uint16_t cmd = 0x0;
    uint16_t addr = 0x11;
    int nec_tx_num = RMT_TX_DATA_NUM;
    for(;;) {
        ESP_LOGI(NEC_TAG, "RMT TX DATA");
        size_t size = (sizeof(rmt_item32_t) * NEC_DATA_ITEM_NUM * nec_tx_num);
        //each item represent a cycle of waveform.
        rmt_item32_t* item = (rmt_item32_t*) malloc(size);
        int item_num = NEC_DATA_ITEM_NUM * nec_tx_num;
        memset((void*) item, 0, size);
        int i, offset = 0;
        while(1) {
            //To build a series of waveforms.
            i = nec_build_items(channel, item + offset, item_num - offset, ((~addr) << 8) | addr, ((~cmd) << 8) |  cmd);
            if(i < 0) {
                break;
            }
            cmd++;
            addr++;
            offset += i;
        }
        //To send data according to the waveform items.
        rmt_write_items(channel, item, item_num, true);
        //Wait until sending is done.
        rmt_wait_tx_done(channel, portMAX_DELAY);
        //before we free the data, make sure sending is already done.
        free(item);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}