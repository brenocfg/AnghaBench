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
typedef  int rmt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RMT_CHANNEL_ERROR_STR ; 
 int RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_clr_intr_enable_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_set_intr_enable_mask (int /*<<< orphan*/ ) ; 

esp_err_t rmt_set_rx_intr_en(rmt_channel_t channel, bool en)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    if(en) {
        rmt_set_intr_enable_mask(BIT(channel * 3 + 1));
    } else {
        rmt_clr_intr_enable_mask(BIT(channel * 3 + 1));
    }
    return ESP_OK;
}