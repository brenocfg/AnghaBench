#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  size_t rmt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {TYPE_1__* tx_lim_ch; } ;
struct TYPE_3__ {int limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RMT ; 
 char* RMT_CHANNEL_ERROR_STR ; 
 size_t RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmt_clr_intr_enable_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_set_intr_enable_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_set_tx_wrap_en (int) ; 
 int /*<<< orphan*/  rmt_spinlock ; 

esp_err_t rmt_set_tx_thr_intr_en(rmt_channel_t channel, bool en, uint16_t evt_thresh)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    if(en) {
        RMT_CHECK(evt_thresh <= 256, "RMT EVT THRESH ERR", ESP_ERR_INVALID_ARG);
        portENTER_CRITICAL(&rmt_spinlock);
        RMT.tx_lim_ch[channel].limit = evt_thresh;
        portEXIT_CRITICAL(&rmt_spinlock);
        rmt_set_tx_wrap_en(true);
#ifdef CONFIG_IDF_TARGET_ESP32
        rmt_set_intr_enable_mask(BIT(channel + 24));
    } else {
        rmt_clr_intr_enable_mask(BIT(channel + 24));
#elif defined CONFIG_IDF_TARGET_ESP32S2BETA
        rmt_set_intr_enable_mask(BIT(channel + 12));
    } else {
        rmt_clr_intr_enable_mask(BIT(channel + 12));
#endif
    }
    return ESP_OK;
}