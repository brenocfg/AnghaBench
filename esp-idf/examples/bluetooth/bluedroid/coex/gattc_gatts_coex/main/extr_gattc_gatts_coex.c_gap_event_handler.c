#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int esp_gap_ble_cb_event_t ;
struct TYPE_15__ {int /*<<< orphan*/  ble_addr_type; int /*<<< orphan*/  bda; int /*<<< orphan*/  ble_adv; int /*<<< orphan*/  search_evt; } ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
struct TYPE_13__ {int /*<<< orphan*/  status; } ;
struct TYPE_12__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  conn_int; int /*<<< orphan*/  max_int; int /*<<< orphan*/  min_int; int /*<<< orphan*/  status; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; } ;
struct TYPE_16__ {TYPE_6__ scan_rst; TYPE_5__ scan_start_cmpl; TYPE_4__ scan_stop_cmpl; TYPE_3__ update_conn_params; TYPE_2__ adv_stop_cmpl; TYPE_1__ adv_start_cmpl; } ;
typedef  TYPE_7__ esp_ble_gap_cb_param_t ;
struct TYPE_17__ {int /*<<< orphan*/  gattc_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_TAG ; 
 int /*<<< orphan*/  ESP_BLE_AD_TYPE_NAME_CMPL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
#define  ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT 138 
#define  ESP_GAP_BLE_ADV_START_COMPLETE_EVT 137 
#define  ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT 136 
#define  ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT 135 
#define  ESP_GAP_BLE_SCAN_RESULT_EVT 134 
#define  ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT 133 
#define  ESP_GAP_BLE_SCAN_START_COMPLETE_EVT 132 
#define  ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT 131 
#define  ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT 130 
#define  ESP_GAP_SEARCH_INQ_CMPL_EVT 129 
#define  ESP_GAP_SEARCH_INQ_RES_EVT 128 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 size_t GATTC_PROFILE_C_APP_ID ; 
 int /*<<< orphan*/  adv_config_done ; 
 int /*<<< orphan*/  adv_config_flag ; 
 int /*<<< orphan*/  adv_params ; 
 int connect ; 
 int /*<<< orphan*/  esp_ble_gap_start_advertising (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gap_start_scanning (int) ; 
 int /*<<< orphan*/  esp_ble_gap_stop_scanning () ; 
 int /*<<< orphan*/  esp_ble_gattc_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * esp_ble_resolve_adv_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_8__* gattc_profile_tab ; 
 int /*<<< orphan*/  remote_device_name ; 
 int /*<<< orphan*/  scan_rsp_config_flag ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;

    switch (event) {

    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~adv_config_flag);
        if (adv_config_done == 0) {
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~scan_rsp_config_flag);
        if (adv_config_done == 0) {
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;

    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(COEX_TAG, "Advertising start failed\n");
        }
        ESP_LOGI(COEX_TAG, "Advertising start successfully\n");
        break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(COEX_TAG, "Advertising stop failed\n");
        } else {
            ESP_LOGI(COEX_TAG, "Stop adv successfully\n");
        }
        break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
         ESP_LOGI(COEX_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d\n",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
        break;
    case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
        if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(COEX_TAG, "scan stop failed, error status = %x\n", param->scan_stop_cmpl.status);
            break;
        }
        ESP_LOGI(COEX_TAG, "ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT, stop scan successfully\n");
        break;
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
        ESP_LOGI(COEX_TAG, "ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT, set scan sparameters complete\n");
        //the unit of the duration is second
        uint32_t duration = 120;
        esp_ble_gap_start_scanning(duration);
        break;
    }
    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(COEX_TAG, "scan start failed, error status = %x\n", param->scan_start_cmpl.status);
            break;
        }
        ESP_LOGI(COEX_TAG, "ESP_GAP_BLE_SCAN_START_COMPLETE_EVT, scan start success\n");
        break;
    case ESP_GAP_BLE_SCAN_RESULT_EVT: {
        esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
        switch (scan_result->scan_rst.search_evt) {
        case ESP_GAP_SEARCH_INQ_RES_EVT:
            adv_name = esp_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
                                                ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
            if (adv_name != NULL) {
                if (strlen(remote_device_name) == adv_name_len && strncmp((char *)adv_name, remote_device_name, adv_name_len) == 0) {
                    if (connect == false) {
                        connect = true;
                        ESP_LOGI(COEX_TAG, "connect to the remote device %s\n", remote_device_name);
                        esp_ble_gap_stop_scanning();
                        esp_ble_gattc_open(gattc_profile_tab[GATTC_PROFILE_C_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
                    }
                }
            }
            break;
        case ESP_GAP_SEARCH_INQ_CMPL_EVT:
             ESP_LOGI(COEX_TAG, "ESP_GAP_SEARCH_INQ_CMPL_EVT, scan stop\n");
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}