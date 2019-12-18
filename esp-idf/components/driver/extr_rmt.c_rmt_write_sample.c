#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_13__ {int intr_alloc_flags; size_t sample_size_remain; int tx_sub_len; int translator; int wait_done; int /*<<< orphan*/  tx_sem; int /*<<< orphan*/  const* sample_cur; scalar_t__ tx_len_rem; scalar_t__ tx_offset; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  (* sample_to_rmt ) (void*,int /*<<< orphan*/ ,size_t,int const,size_t*,size_t*) ;} ;
typedef  TYPE_5__ rmt_obj_t ;
typedef  size_t rmt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_15__ {TYPE_2__* conf_ch; } ;
struct TYPE_14__ {TYPE_4__* chan; } ;
struct TYPE_12__ {TYPE_3__* data32; } ;
struct TYPE_11__ {scalar_t__ val; } ;
struct TYPE_9__ {int mem_size; } ;
struct TYPE_10__ {TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int ESP_INTR_FLAG_IRAM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_8__ RMT ; 
 TYPE_7__ RMTMEM ; 
 int /*<<< orphan*/  RMT_CHANNEL_ERROR_STR ; 
 size_t RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RMT_DRIVER_ERROR_STR ; 
 int RMT_MEM_ITEM_NUM ; 
 int /*<<< orphan*/  RMT_PSRAM_BUFFER_WARN_STR ; 
 int /*<<< orphan*/  RMT_TAG ; 
 int /*<<< orphan*/  RMT_TRANSLATOR_UNINIT_STR ; 
 int /*<<< orphan*/  esp_ptr_internal (int /*<<< orphan*/  const*) ; 
 TYPE_5__** p_rmt_obj ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  rmt_fill_memory (size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_set_tx_thr_intr_en (size_t,int,int const) ; 
 int /*<<< orphan*/  rmt_tx_start (size_t,int) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,size_t,int const,size_t*,size_t*) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t rmt_write_sample(rmt_channel_t channel, const uint8_t *src, size_t src_size, bool wait_tx_done)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT_CHECK(p_rmt_obj[channel] != NULL, RMT_DRIVER_ERROR_STR, ESP_FAIL);
    RMT_CHECK(p_rmt_obj[channel]->sample_to_rmt != NULL,RMT_TRANSLATOR_UNINIT_STR, ESP_FAIL);
#if CONFIG_SPIRAM_USE_MALLOC
    if( p_rmt_obj[channel]->intr_alloc_flags & ESP_INTR_FLAG_IRAM ) {
        if( !esp_ptr_internal(src) ) {
            ESP_LOGE(RMT_TAG, RMT_PSRAM_BUFFER_WARN_STR);
            return ESP_ERR_INVALID_ARG;
        }
    }
#endif
    size_t item_num = 0;
    size_t translated_size = 0;
    rmt_obj_t* p_rmt = p_rmt_obj[channel];
    const uint32_t item_block_len = RMT.conf_ch[channel].conf0.mem_size * RMT_MEM_ITEM_NUM;
    const uint32_t item_sub_len = item_block_len / 2;
    xSemaphoreTake(p_rmt->tx_sem, portMAX_DELAY);
    p_rmt->sample_to_rmt((void *)src, p_rmt->tx_buf, src_size, item_block_len, &translated_size, &item_num);
    p_rmt->sample_size_remain = src_size - translated_size;
    p_rmt->sample_cur = src + translated_size;
    rmt_fill_memory(channel, p_rmt->tx_buf, item_num, 0);
    if (item_num == item_block_len) {
        rmt_set_tx_thr_intr_en(channel, 1, item_sub_len);
        p_rmt->tx_data = p_rmt->tx_buf;
        p_rmt->tx_offset = 0;
        p_rmt->tx_sub_len = item_sub_len;
        p_rmt->translator = true;
    } else {
        RMTMEM.chan[channel].data32[item_num].val = 0;
        p_rmt->tx_len_rem = 0;
        p_rmt->sample_cur = NULL;
        p_rmt->translator = false;
    }
    rmt_tx_start(channel, true);
    p_rmt->wait_done = wait_tx_done;
    if (wait_tx_done) {
        xSemaphoreTake(p_rmt->tx_sem, portMAX_DELAY);
        xSemaphoreGive(p_rmt->tx_sem);
    }
    return ESP_OK;
}