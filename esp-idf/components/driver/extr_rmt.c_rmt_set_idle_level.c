#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rmt_idle_level_t ;
typedef  size_t rmt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_2__* conf_ch; } ;
struct TYPE_4__ {int idle_out_en; scalar_t__ idle_out_lv; } ;
struct TYPE_5__ {TYPE_1__ conf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ RMT ; 
 char* RMT_CHANNEL_ERROR_STR ; 
 size_t RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ RMT_IDLE_LEVEL_MAX ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmt_spinlock ; 

esp_err_t rmt_set_idle_level(rmt_channel_t channel, bool idle_out_en, rmt_idle_level_t level)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT_CHECK(level < RMT_IDLE_LEVEL_MAX, "RMT IDLE LEVEL ERR", ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&rmt_spinlock);
    RMT.conf_ch[channel].conf1.idle_out_en = idle_out_en;
    RMT.conf_ch[channel].conf1.idle_out_lv = level;
    portEXIT_CRITICAL(&rmt_spinlock);
    return ESP_OK;
}