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
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  play_pos; int /*<<< orphan*/  playback; } ;
typedef  TYPE_1__ esp_avrc_rn_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_AV_TAG ; 
#define  ESP_AVRC_RN_PLAY_POS_CHANGED 130 
#define  ESP_AVRC_RN_PLAY_STATUS_CHANGE 129 
#define  ESP_AVRC_RN_TRACK_CHANGE 128 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_av_new_track () ; 
 int /*<<< orphan*/  bt_av_play_pos_changed () ; 
 int /*<<< orphan*/  bt_av_playback_changed () ; 

void bt_av_notify_evt_handler(uint8_t event_id, esp_avrc_rn_param_t *event_parameter)
{
    switch (event_id) {
    case ESP_AVRC_RN_TRACK_CHANGE:
        bt_av_new_track();
        break;
    case ESP_AVRC_RN_PLAY_STATUS_CHANGE:
        ESP_LOGI(BT_AV_TAG, "Playback status changed: 0x%x", event_parameter->playback);
        bt_av_playback_changed();
        break;
    case ESP_AVRC_RN_PLAY_POS_CHANGED:
        ESP_LOGI(BT_AV_TAG, "Play position changed: %d-ms", event_parameter->play_pos);
        bt_av_play_pos_changed();
        break;
    }
}