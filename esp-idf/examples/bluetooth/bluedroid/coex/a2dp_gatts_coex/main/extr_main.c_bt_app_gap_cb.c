#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int passkey; } ;
struct TYPE_6__ {int num_val; int /*<<< orphan*/  bda; } ;
struct TYPE_8__ {int device_name; int /*<<< orphan*/  stat; int /*<<< orphan*/  bda; } ;
struct TYPE_9__ {TYPE_2__ key_notif; TYPE_1__ cfm_req; TYPE_3__ auth_cmpl; } ;
typedef  TYPE_4__ esp_bt_gap_cb_param_t ;
typedef  int esp_bt_gap_cb_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_BLE_COEX_TAG ; 
 int /*<<< orphan*/  ESP_BD_ADDR_LEN ; 
#define  ESP_BT_GAP_AUTH_CMPL_EVT 131 
#define  ESP_BT_GAP_CFM_REQ_EVT 130 
#define  ESP_BT_GAP_KEY_NOTIF_EVT 129 
#define  ESP_BT_GAP_KEY_REQ_EVT 128 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  esp_bt_gap_ssp_confirm_reply (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_BT_GAP_AUTH_CMPL_EVT: {
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(BT_BLE_COEX_TAG, "authentication success: %s", param->auth_cmpl.device_name);
            esp_log_buffer_hex(BT_BLE_COEX_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
        } else {
            ESP_LOGE(BT_BLE_COEX_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
        }
        break;
    }
#if (CONFIG_BT_SSP_ENABLED == true)
    case ESP_BT_GAP_CFM_REQ_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %d", param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%d", param->key_notif.passkey);
        break;
    case ESP_BT_GAP_KEY_REQ_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
        break;
#endif
    default: {
        ESP_LOGI(BT_BLE_COEX_TAG, "event: %d", event);
        break;
    }
    }
    return;
}