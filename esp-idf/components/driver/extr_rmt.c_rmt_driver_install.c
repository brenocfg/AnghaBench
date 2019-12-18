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
struct TYPE_4__ {size_t channel; int wait_done; int translator; int intr_alloc_flags; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_sem; int /*<<< orphan*/  tx_sem_buffer; int /*<<< orphan*/ * sample_to_rmt; scalar_t__ tx_sub_len; scalar_t__ tx_offset; int /*<<< orphan*/ * tx_data; scalar_t__ tx_len_rem; } ;
typedef  TYPE_1__ rmt_obj_t ;
typedef  size_t rmt_channel_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int BIT (size_t) ; 
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int ESP_INTR_FLAG_IRAM ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int MALLOC_CAP_8BIT ; 
 int MALLOC_CAP_INTERNAL ; 
 int /*<<< orphan*/  RINGBUF_TYPE_NOSPLIT ; 
 char* RMT_CHANNEL_ERROR_STR ; 
 size_t RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  RMT_TAG ; 
 int /*<<< orphan*/  _lock_acquire_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release_recursive (int /*<<< orphan*/ *) ; 
 scalar_t__ heap_caps_calloc (int,int,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__** p_rmt_obj ; 
 int /*<<< orphan*/  rmt_driver_isr_default ; 
 int /*<<< orphan*/  rmt_driver_isr_lock ; 
 scalar_t__ rmt_isr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmt_set_err_intr_en (size_t,int) ; 
 int /*<<< orphan*/  rmt_set_rx_intr_en (size_t,int) ; 
 int /*<<< orphan*/  rmt_set_tx_intr_en (size_t,int) ; 
 int s_rmt_driver_channels ; 
 int /*<<< orphan*/  s_rmt_driver_intr_handle ; 
 int /*<<< orphan*/ * xRingbufferCreate (size_t,int /*<<< orphan*/ ) ; 
 void* xSemaphoreCreateBinary () ; 
 int /*<<< orphan*/ * xSemaphoreCreateBinaryStatic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ *) ; 

esp_err_t rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int intr_alloc_flags)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT_CHECK((s_rmt_driver_channels & BIT(channel)) == 0, "RMT driver already installed for channel", ESP_ERR_INVALID_STATE);

    esp_err_t err = ESP_OK;

    if(p_rmt_obj[channel] != NULL) {
        ESP_LOGD(RMT_TAG, "RMT driver already installed");
        return ESP_ERR_INVALID_STATE;
    }

#if !CONFIG_SPIRAM_USE_MALLOC
    p_rmt_obj[channel] = (rmt_obj_t*) malloc(sizeof(rmt_obj_t));
#else
    if( !(intr_alloc_flags & ESP_INTR_FLAG_IRAM) ) {
        p_rmt_obj[channel] = (rmt_obj_t*) malloc(sizeof(rmt_obj_t));
    } else {
        p_rmt_obj[channel] = (rmt_obj_t*) heap_caps_calloc(1, sizeof(rmt_obj_t), MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT);
    }
#endif

    if(p_rmt_obj[channel] == NULL) {
        ESP_LOGE(RMT_TAG, "RMT driver malloc error");
        return ESP_ERR_NO_MEM;
    }
    memset(p_rmt_obj[channel], 0, sizeof(rmt_obj_t));

    p_rmt_obj[channel]->tx_len_rem = 0;
    p_rmt_obj[channel]->tx_data = NULL;
    p_rmt_obj[channel]->channel = channel;
    p_rmt_obj[channel]->tx_offset = 0;
    p_rmt_obj[channel]->tx_sub_len = 0;
    p_rmt_obj[channel]->wait_done = false;
    p_rmt_obj[channel]->translator = false;
    p_rmt_obj[channel]->sample_to_rmt = NULL;
    if(p_rmt_obj[channel]->tx_sem == NULL) {
#if !CONFIG_SPIRAM_USE_MALLOC
        p_rmt_obj[channel]->tx_sem = xSemaphoreCreateBinary();
#else
        p_rmt_obj[channel]->intr_alloc_flags = intr_alloc_flags;
        if( !(intr_alloc_flags & ESP_INTR_FLAG_IRAM) ) {
            p_rmt_obj[channel]->tx_sem = xSemaphoreCreateBinary();
        } else {
            p_rmt_obj[channel]->tx_sem = xSemaphoreCreateBinaryStatic(&p_rmt_obj[channel]->tx_sem_buffer);
        }
#endif
        xSemaphoreGive(p_rmt_obj[channel]->tx_sem);
    }
    if(p_rmt_obj[channel]->rx_buf == NULL && rx_buf_size > 0) {
        p_rmt_obj[channel]->rx_buf = xRingbufferCreate(rx_buf_size, RINGBUF_TYPE_NOSPLIT);
        rmt_set_rx_intr_en(channel, 1);
        rmt_set_err_intr_en(channel, 1);
    }

    _lock_acquire_recursive(&rmt_driver_isr_lock);

    if(s_rmt_driver_channels == 0) { // first RMT channel using driver
        err = rmt_isr_register(rmt_driver_isr_default, NULL, intr_alloc_flags, &s_rmt_driver_intr_handle);
    }
    if (err == ESP_OK) {
        s_rmt_driver_channels |= BIT(channel);
        rmt_set_tx_intr_en(channel, 1);
    }

    _lock_release_recursive(&rmt_driver_isr_lock);

    return err;
}