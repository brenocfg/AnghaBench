#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ volume; } ;
typedef  TYPE_1__ esp_avrc_rn_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_RC_TG_TAG ; 
 int /*<<< orphan*/  ESP_AVRC_RN_RSP_CHANGED ; 
 int /*<<< orphan*/  ESP_AVRC_RN_VOLUME_CHANGE ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_avrc_tg_send_rn_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ s_volume ; 
 int /*<<< orphan*/  s_volume_lock ; 
 int s_volume_notify ; 

__attribute__((used)) static void volume_set_by_local_host(uint8_t volume)
{
    ESP_LOGI(BT_RC_TG_TAG, "Volume is set locally to: %d%%", (uint32_t)volume * 100 / 0x7f);
    _lock_acquire(&s_volume_lock);
    s_volume = volume;
    _lock_release(&s_volume_lock);

    if (s_volume_notify) {
        esp_avrc_rn_param_t rn_param;
        rn_param.volume = s_volume;
        esp_avrc_tg_send_rn_rsp(ESP_AVRC_RN_VOLUME_CHANGE, ESP_AVRC_RN_RSP_CHANGED, &rn_param);
        s_volume_notify = false;
    }
}