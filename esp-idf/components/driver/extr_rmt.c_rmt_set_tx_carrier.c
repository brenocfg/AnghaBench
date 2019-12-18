#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  size_t rmt_channel_t ;
typedef  scalar_t__ rmt_carrier_level_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {TYPE_2__* conf_ch; TYPE_3__* carrier_duty_ch; } ;
struct TYPE_7__ {void* low; void* high; } ;
struct TYPE_5__ {int carrier_en; scalar_t__ carrier_out_lv; } ;
struct TYPE_6__ {TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_4__ RMT ; 
 int /*<<< orphan*/  RMT_CARRIER_ERROR_STR ; 
 scalar_t__ RMT_CARRIER_LEVEL_MAX ; 
 int /*<<< orphan*/  RMT_CHANNEL_ERROR_STR ; 
 size_t RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t rmt_set_tx_carrier(rmt_channel_t channel, bool carrier_en, uint16_t high_level, uint16_t low_level,
    rmt_carrier_level_t carrier_level)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT_CHECK(carrier_level < RMT_CARRIER_LEVEL_MAX, RMT_CARRIER_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT.carrier_duty_ch[channel].high = high_level;
    RMT.carrier_duty_ch[channel].low = low_level;
    RMT.conf_ch[channel].conf0.carrier_out_lv = carrier_level;
    RMT.conf_ch[channel].conf0.carrier_en = carrier_en;
    return ESP_OK;
}