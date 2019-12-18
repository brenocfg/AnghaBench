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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {TYPE_1__ media_ctrl_stat; } ;
typedef  TYPE_2__ esp_a2d_cb_param_t ;

/* Variables and functions */
#define  APP_AV_MEDIA_STATE_IDLE 131 
#define  APP_AV_MEDIA_STATE_STARTED 130 
#define  APP_AV_MEDIA_STATE_STARTING 129 
#define  APP_AV_MEDIA_STATE_STOPPING 128 
 int /*<<< orphan*/  APP_AV_STATE_DISCONNECTING ; 
 int /*<<< orphan*/  BT_APP_HEART_BEAT_EVT ; 
 int /*<<< orphan*/  BT_AV_TAG ; 
 int /*<<< orphan*/  ESP_A2D_MEDIA_CTRL_ACK_EVT ; 
 int /*<<< orphan*/  ESP_A2D_MEDIA_CTRL_ACK_SUCCESS ; 
 int /*<<< orphan*/  ESP_A2D_MEDIA_CTRL_CHECK_SRC_RDY ; 
 int /*<<< orphan*/  ESP_A2D_MEDIA_CTRL_START ; 
 int /*<<< orphan*/  ESP_A2D_MEDIA_CTRL_STOP ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esp_a2d_media_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_a2d_source_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_a2d_state ; 
 int s_intv_cnt ; 
 int s_media_state ; 
 int /*<<< orphan*/  s_peer_bda ; 

__attribute__((used)) static void bt_app_av_media_proc(uint16_t event, void *param)
{
    esp_a2d_cb_param_t *a2d = NULL;
    switch (s_media_state) {
    case APP_AV_MEDIA_STATE_IDLE: {
        if (event == BT_APP_HEART_BEAT_EVT) {
            ESP_LOGI(BT_AV_TAG, "a2dp media ready checking ...");
            esp_a2d_media_ctrl(ESP_A2D_MEDIA_CTRL_CHECK_SRC_RDY);
        } else if (event == ESP_A2D_MEDIA_CTRL_ACK_EVT) {
            a2d = (esp_a2d_cb_param_t *)(param);
            if (a2d->media_ctrl_stat.cmd == ESP_A2D_MEDIA_CTRL_CHECK_SRC_RDY &&
                    a2d->media_ctrl_stat.status == ESP_A2D_MEDIA_CTRL_ACK_SUCCESS) {
                ESP_LOGI(BT_AV_TAG, "a2dp media ready, starting ...");
                esp_a2d_media_ctrl(ESP_A2D_MEDIA_CTRL_START);
                s_media_state = APP_AV_MEDIA_STATE_STARTING;
            }
        }
        break;
    }
    case APP_AV_MEDIA_STATE_STARTING: {
        if (event == ESP_A2D_MEDIA_CTRL_ACK_EVT) {
            a2d = (esp_a2d_cb_param_t *)(param);
            if (a2d->media_ctrl_stat.cmd == ESP_A2D_MEDIA_CTRL_START &&
                    a2d->media_ctrl_stat.status == ESP_A2D_MEDIA_CTRL_ACK_SUCCESS) {
                ESP_LOGI(BT_AV_TAG, "a2dp media start successfully.");
                s_intv_cnt = 0;
                s_media_state = APP_AV_MEDIA_STATE_STARTED;
            } else {
                // not started succesfully, transfer to idle state
                ESP_LOGI(BT_AV_TAG, "a2dp media start failed.");
                s_media_state = APP_AV_MEDIA_STATE_IDLE;
            }
        }
        break;
    }
    case APP_AV_MEDIA_STATE_STARTED: {
        if (event == BT_APP_HEART_BEAT_EVT) {
            if (++s_intv_cnt >= 10) {
                ESP_LOGI(BT_AV_TAG, "a2dp media stopping...");
                esp_a2d_media_ctrl(ESP_A2D_MEDIA_CTRL_STOP);
                s_media_state = APP_AV_MEDIA_STATE_STOPPING;
                s_intv_cnt = 0;
            }
        }
        break;
    }
    case APP_AV_MEDIA_STATE_STOPPING: {
        if (event == ESP_A2D_MEDIA_CTRL_ACK_EVT) {
            a2d = (esp_a2d_cb_param_t *)(param);
            if (a2d->media_ctrl_stat.cmd == ESP_A2D_MEDIA_CTRL_STOP &&
                    a2d->media_ctrl_stat.status == ESP_A2D_MEDIA_CTRL_ACK_SUCCESS) {
                ESP_LOGI(BT_AV_TAG, "a2dp media stopped successfully, disconnecting...");
                s_media_state = APP_AV_MEDIA_STATE_IDLE;
                esp_a2d_source_disconnect(s_peer_bda);
                s_a2d_state = APP_AV_STATE_DISCONNECTING;
            } else {
                ESP_LOGI(BT_AV_TAG, "a2dp media stopping...");
                esp_a2d_media_ctrl(ESP_A2D_MEDIA_CTRL_STOP);
            }
        }
        break;
    }
    }
}