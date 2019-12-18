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
typedef  int /*<<< orphan*/  esp_avrc_ct_cb_param_t ;
typedef  int esp_avrc_ct_cb_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_RC_CT_TAG ; 
#define  ESP_AVRC_CT_CHANGE_NOTIFY_EVT 134 
#define  ESP_AVRC_CT_CONNECTION_STATE_EVT 133 
#define  ESP_AVRC_CT_GET_RN_CAPABILITIES_RSP_EVT 132 
#define  ESP_AVRC_CT_METADATA_RSP_EVT 131 
#define  ESP_AVRC_CT_PASSTHROUGH_RSP_EVT 130 
#define  ESP_AVRC_CT_REMOTE_FEATURES_EVT 129 
#define  ESP_AVRC_CT_SET_ABSOLUTE_VOLUME_RSP_EVT 128 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bt_app_work_dispatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_av_hdl_avrc_ct_evt ; 

__attribute__((used)) static void bt_app_rc_ct_cb(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param)
{
    switch (event) {
    case ESP_AVRC_CT_METADATA_RSP_EVT:
    case ESP_AVRC_CT_CONNECTION_STATE_EVT:
    case ESP_AVRC_CT_PASSTHROUGH_RSP_EVT:
    case ESP_AVRC_CT_CHANGE_NOTIFY_EVT:
    case ESP_AVRC_CT_REMOTE_FEATURES_EVT:
    case ESP_AVRC_CT_GET_RN_CAPABILITIES_RSP_EVT:
    case ESP_AVRC_CT_SET_ABSOLUTE_VOLUME_RSP_EVT: {
        bt_app_work_dispatch(bt_av_hdl_avrc_ct_evt, event, param, sizeof(esp_avrc_ct_cb_param_t), NULL);
        break;
    }
    default:
        ESP_LOGE(BT_RC_CT_TAG, "Invalid AVRC event: %d", event);
        break;
    }
}