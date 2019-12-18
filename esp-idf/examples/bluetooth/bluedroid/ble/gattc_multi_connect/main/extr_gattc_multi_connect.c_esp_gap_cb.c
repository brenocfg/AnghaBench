#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int esp_gap_ble_cb_event_t ;
struct TYPE_13__ {int /*<<< orphan*/  status; } ;
struct TYPE_12__ {int /*<<< orphan*/  status; } ;
struct TYPE_11__ {int /*<<< orphan*/  ble_addr_type; int /*<<< orphan*/  bda; int /*<<< orphan*/  ble_adv; int /*<<< orphan*/  scan_rsp_len; int /*<<< orphan*/  adv_data_len; int /*<<< orphan*/  search_evt; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; } ;
struct TYPE_9__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  conn_int; int /*<<< orphan*/  max_int; int /*<<< orphan*/  min_int; int /*<<< orphan*/  status; } ;
struct TYPE_14__ {TYPE_5__ adv_stop_cmpl; TYPE_4__ scan_stop_cmpl; TYPE_3__ scan_rst; TYPE_2__ scan_start_cmpl; TYPE_1__ update_conn_params; } ;
typedef  TYPE_6__ esp_ble_gap_cb_param_t ;
struct TYPE_15__ {int /*<<< orphan*/  gattc_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_AD_TYPE_NAME_CMPL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
#define  ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT 135 
#define  ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT 134 
#define  ESP_GAP_BLE_SCAN_RESULT_EVT 133 
#define  ESP_GAP_BLE_SCAN_START_COMPLETE_EVT 132 
#define  ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT 131 
#define  ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT 130 
#define  ESP_GAP_SEARCH_INQ_CMPL_EVT 129 
#define  ESP_GAP_SEARCH_INQ_RES_EVT 128 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  GATTC_TAG ; 
 int Isconnecting ; 
 size_t PROFILE_A_APP_ID ; 
 size_t PROFILE_B_APP_ID ; 
 size_t PROFILE_C_APP_ID ; 
 int conn_device_a ; 
 int conn_device_b ; 
 int conn_device_c ; 
 int /*<<< orphan*/  esp_ble_gap_start_scanning (int) ; 
 int /*<<< orphan*/  esp_ble_gap_stop_scanning () ; 
 int /*<<< orphan*/  esp_ble_gattc_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * esp_ble_resolve_adv_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_log_buffer_char (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* gl_profile_tab ; 
 int /*<<< orphan*/ * remote_device_name ; 
 int stop_scan_done ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;
    switch (event) {
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
         ESP_LOGI(GATTC_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
        break;
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
        //the unit of the duration is second
        uint32_t duration = 30;
        esp_ble_gap_start_scanning(duration);
        break;
    }
    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        //scan start complete event to indicate scan start successfully or failed
        if (param->scan_start_cmpl.status == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(GATTC_TAG, "Scan start success");
        }else{
            ESP_LOGE(GATTC_TAG, "Scan start failed");
        }
        break;
    case ESP_GAP_BLE_SCAN_RESULT_EVT: {
        esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
        switch (scan_result->scan_rst.search_evt) {
        case ESP_GAP_SEARCH_INQ_RES_EVT:
            esp_log_buffer_hex(GATTC_TAG, scan_result->scan_rst.bda, 6);
            ESP_LOGI(GATTC_TAG, "Searched Adv Data Len %d, Scan Response Len %d", scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);
            adv_name = esp_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
                                                ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
            ESP_LOGI(GATTC_TAG, "Searched Device Name Len %d", adv_name_len);
            esp_log_buffer_char(GATTC_TAG, adv_name, adv_name_len);
            ESP_LOGI(GATTC_TAG, "\n");
            if (Isconnecting){
                break;
            }
            if (conn_device_a && conn_device_b && conn_device_c && !stop_scan_done){
                stop_scan_done = true;
                esp_ble_gap_stop_scanning();
                ESP_LOGI(GATTC_TAG, "all devices are connected");
                break;
            }
            if (adv_name != NULL) {

                if (strlen(remote_device_name[0]) == adv_name_len && strncmp((char *)adv_name, remote_device_name[0], adv_name_len) == 0) {
                    if (conn_device_a == false) {
                        conn_device_a = true;
                        ESP_LOGI(GATTC_TAG, "Searched device %s", remote_device_name[0]);
                        esp_ble_gap_stop_scanning();
                        esp_ble_gattc_open(gl_profile_tab[PROFILE_A_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
                        Isconnecting = true;
                    }
                    break;
                }
                else if (strlen(remote_device_name[1]) == adv_name_len && strncmp((char *)adv_name, remote_device_name[1], adv_name_len) == 0) {
                    if (conn_device_b == false) {
                        conn_device_b = true;
                        ESP_LOGI(GATTC_TAG, "Searched device %s", remote_device_name[1]);
                        esp_ble_gap_stop_scanning();
                        esp_ble_gattc_open(gl_profile_tab[PROFILE_B_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
                        Isconnecting = true;

                    }
                }
                else if (strlen(remote_device_name[2]) == adv_name_len && strncmp((char *)adv_name, remote_device_name[2], adv_name_len) == 0) {
                    if (conn_device_c == false) {
                        conn_device_c = true;
                        ESP_LOGI(GATTC_TAG, "Searched device %s", remote_device_name[2]);
                        esp_ble_gap_stop_scanning();
                        esp_ble_gattc_open(gl_profile_tab[PROFILE_C_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
                        Isconnecting = true;
                    }
                    break;
                }

            }
            break;
        case ESP_GAP_SEARCH_INQ_CMPL_EVT:
            break;
        default:
            break;
        }
        break;
    }

    case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
        if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){
            ESP_LOGE(GATTC_TAG, "Scan stop failed");
            break;
        }
        ESP_LOGI(GATTC_TAG, "Stop scan successfully");

        break;

    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){
            ESP_LOGE(GATTC_TAG, "Adv stop failed");
            break;
        }
        ESP_LOGI(GATTC_TAG, "Stop adv successfully");
        break;

    default:
        break;
    }
}