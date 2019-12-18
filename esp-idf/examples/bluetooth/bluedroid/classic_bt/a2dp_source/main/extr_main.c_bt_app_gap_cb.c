#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char* esp_bt_pin_code_t ;
struct TYPE_13__ {int passkey; } ;
struct TYPE_12__ {int num_val; int /*<<< orphan*/  bda; } ;
struct TYPE_11__ {int min_16_digit; int /*<<< orphan*/  bda; } ;
struct TYPE_10__ {int device_name; int /*<<< orphan*/  stat; int /*<<< orphan*/  bda; } ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct TYPE_14__ {TYPE_5__ key_notif; TYPE_4__ cfm_req; TYPE_3__ pin_req; TYPE_2__ auth_cmpl; TYPE_1__ disc_st_chg; } ;
typedef  TYPE_6__ esp_bt_gap_cb_param_t ;
typedef  int esp_bt_gap_cb_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_AV_STATE_CONNECTING ; 
 int /*<<< orphan*/  APP_AV_STATE_DISCOVERED ; 
 int /*<<< orphan*/  BT_AV_TAG ; 
 int /*<<< orphan*/  ESP_BD_ADDR_LEN ; 
#define  ESP_BT_GAP_AUTH_CMPL_EVT 136 
#define  ESP_BT_GAP_CFM_REQ_EVT 135 
 int /*<<< orphan*/  ESP_BT_GAP_DISCOVERY_STARTED ; 
 int /*<<< orphan*/  ESP_BT_GAP_DISCOVERY_STOPPED ; 
#define  ESP_BT_GAP_DISC_RES_EVT 134 
#define  ESP_BT_GAP_DISC_STATE_CHANGED_EVT 133 
#define  ESP_BT_GAP_KEY_NOTIF_EVT 132 
#define  ESP_BT_GAP_KEY_REQ_EVT 131 
#define  ESP_BT_GAP_PIN_REQ_EVT 130 
#define  ESP_BT_GAP_RMT_SRVCS_EVT 129 
#define  ESP_BT_GAP_RMT_SRVC_REC_EVT 128 
 int /*<<< orphan*/  ESP_BT_INQ_MODE_GENERAL_INQUIRY ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  esp_a2d_source_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_gap_pin_reply (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  esp_bt_gap_ssp_confirm_reply (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_bt_gap_start_discovery (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_inquiry_scan_result (TYPE_6__*) ; 
 int /*<<< orphan*/  s_a2d_state ; 
 int /*<<< orphan*/  s_peer_bda ; 
 int s_peer_bdname ; 

void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_BT_GAP_DISC_RES_EVT: {
        filter_inquiry_scan_result(param);
        break;
    }
    case ESP_BT_GAP_DISC_STATE_CHANGED_EVT: {
        if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STOPPED) {
            if (s_a2d_state == APP_AV_STATE_DISCOVERED) {
                s_a2d_state = APP_AV_STATE_CONNECTING;
                ESP_LOGI(BT_AV_TAG, "Device discovery stopped.");
                ESP_LOGI(BT_AV_TAG, "a2dp connecting to peer: %s", s_peer_bdname);
                esp_a2d_source_connect(s_peer_bda);
            } else {
                // not discovered, continue to discover
                ESP_LOGI(BT_AV_TAG, "Device discovery failed, continue to discover...");
                esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
            }
        } else if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STARTED) {
            ESP_LOGI(BT_AV_TAG, "Discovery started.");
        }
        break;
    }
    case ESP_BT_GAP_RMT_SRVCS_EVT:
    case ESP_BT_GAP_RMT_SRVC_REC_EVT:
        break;
    case ESP_BT_GAP_AUTH_CMPL_EVT: {
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(BT_AV_TAG, "authentication success: %s", param->auth_cmpl.device_name);
            esp_log_buffer_hex(BT_AV_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
        } else {
            ESP_LOGE(BT_AV_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
        }
        break;
    }
    case ESP_BT_GAP_PIN_REQ_EVT: {
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_PIN_REQ_EVT min_16_digit:%d", param->pin_req.min_16_digit);
        if (param->pin_req.min_16_digit) {
            ESP_LOGI(BT_AV_TAG, "Input pin code: 0000 0000 0000 0000");
            esp_bt_pin_code_t pin_code = {0};
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 16, pin_code);
        } else {
            ESP_LOGI(BT_AV_TAG, "Input pin code: 1234");
            esp_bt_pin_code_t pin_code;
            pin_code[0] = '1';
            pin_code[1] = '2';
            pin_code[2] = '3';
            pin_code[3] = '4';
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 4, pin_code);
        }
        break;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    case ESP_BT_GAP_CFM_REQ_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %d", param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%d", param->key_notif.passkey);
        break;
    case ESP_BT_GAP_KEY_REQ_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
        break;
#endif

    default: {
        ESP_LOGI(BT_AV_TAG, "event: %d", event);
        break;
    }
    }
    return;
}