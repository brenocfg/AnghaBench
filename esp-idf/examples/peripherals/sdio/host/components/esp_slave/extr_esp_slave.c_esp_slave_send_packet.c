#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
struct TYPE_4__ {size_t buffer_size; int tx_sent_buffers; int /*<<< orphan*/ * card; } ;
typedef  TYPE_1__ esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ ESP_SLAVE_CMD53_END_ADDR ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  esp_slave_get_tx_buffer_num (TYPE_1__*,size_t*) ; 
 size_t portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  sdmmc_io_write_blocks (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdmmc_io_write_bytes (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 size_t xTaskGetTickCount () ; 

esp_err_t esp_slave_send_packet(esp_slave_context_t *context, const void* start, size_t length, uint32_t wait_ms)
{
    sdmmc_card_t *card = context->card;
    uint16_t buffer_size = context->buffer_size;
    int buffer_used = (length + buffer_size - 1)/buffer_size;
    esp_err_t err;
    const uint32_t wait_ticks = wait_ms/portTICK_PERIOD_MS;
    uint32_t pre = xTaskGetTickCount();

    assert(length>0);
    for(;;) {
        uint32_t num = 0;
        err = esp_slave_get_tx_buffer_num(context, &num);
        if (err == ESP_OK && num * buffer_size >= length) break;
        if (err != ESP_OK && err != ESP_ERR_TIMEOUT) return err;
        //not error and buffer not enough, retry ``timeout_cnt`` times
        uint32_t now = xTaskGetTickCount();
        if (now-pre >= wait_ticks) {
            ESP_LOGD(TAG, "buffer is not enough: %d, %d required.", num, buffer_used);
            return ESP_ERR_TIMEOUT;
        } else {
            ESP_LOGV(TAG, "buffer is not enough: %d, %d required. Retry...", num, buffer_used);
        }
        vTaskDelay(1);
    }

    ESP_LOGV(TAG, "send_packet: len: %d", length);
    uint8_t *start_ptr = (uint8_t*)start;
    uint32_t len_remain = length;
    do {
        const int block_size = 512;
        /* Though the driver supports to split packet of unaligned size into
         * length of 4x and 1~3, we still send aligned size of data to get
         * higher effeciency. The length is determined by the SDIO address, and
         * the remainning will be discard by the slave hardware.
         */
        int block_n = len_remain/block_size;
        int len_to_send;
        if (block_n) {
            len_to_send = block_n * block_size;
            err = sdmmc_io_write_blocks(card, 1, ESP_SLAVE_CMD53_END_ADDR - len_remain, start_ptr, len_to_send);
        } else {
            len_to_send = len_remain;
            err = sdmmc_io_write_bytes(card, 1, ESP_SLAVE_CMD53_END_ADDR - len_remain, start_ptr, (len_to_send + 3) & (~3));
        }
        if (err != ESP_OK) return err;
        start_ptr += len_to_send;
        len_remain -= len_to_send;
    } while (len_remain);

    context->tx_sent_buffers += buffer_used;
    return ESP_OK;
}