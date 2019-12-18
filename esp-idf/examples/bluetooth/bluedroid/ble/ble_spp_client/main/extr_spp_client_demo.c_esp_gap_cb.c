#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int esp_gap_ble_cb_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_19__ {int /*<<< orphan*/  status; } ;
struct TYPE_18__ {int /*<<< orphan*/  ble_adv; int /*<<< orphan*/  scan_rsp_len; int /*<<< orphan*/  adv_data_len; int /*<<< orphan*/  bda; int /*<<< orphan*/  search_evt; } ;
struct TYPE_16__ {int /*<<< orphan*/  status; } ;
struct TYPE_15__ {int /*<<< orphan*/  status; } ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
struct TYPE_20__ {TYPE_6__ adv_stop_cmpl; TYPE_5__ scan_rst; TYPE_3__ scan_stop_cmpl; TYPE_2__ scan_start_cmpl; TYPE_1__ scan_param_cmpl; } ;
typedef  TYPE_7__ esp_ble_gap_cb_param_t ;
struct TYPE_17__ {int /*<<< orphan*/  ble_addr_type; int /*<<< orphan*/  bda; } ;
struct TYPE_21__ {TYPE_4__ scan_rst; } ;
struct TYPE_13__ {int /*<<< orphan*/  gattc_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_AD_TYPE_NAME_CMPL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
#define  ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT 134 
#define  ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT 133 
#define  ESP_GAP_BLE_SCAN_RESULT_EVT 132 
#define  ESP_GAP_BLE_SCAN_START_COMPLETE_EVT 131 
#define  ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT 130 
#define  ESP_GAP_SEARCH_INQ_CMPL_EVT 129 
#define  ESP_GAP_SEARCH_INQ_RES_EVT 128 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  GATTC_TAG ; 
 size_t PROFILE_APP_ID ; 
 int /*<<< orphan*/  device_name ; 
 int /*<<< orphan*/  esp_ble_gap_start_scanning (int) ; 
 int /*<<< orphan*/  esp_ble_gap_stop_scanning () ; 
 int /*<<< orphan*/  esp_ble_gattc_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * esp_ble_resolve_adv_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_err_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_char (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_11__* gl_profile_tab ; 
 int is_connect ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,TYPE_7__*,int) ; 
 TYPE_8__ scan_rst ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;
    esp_err_t err;

    switch(event){
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
        if((err = param->scan_param_cmpl.status) != ESP_BT_STATUS_SUCCESS){
            ESP_LOGE(GATTC_TAG, "Scan param set failed: %s", esp_err_to_name(err));
            break;
        }
        //the unit of the duration is second
        uint32_t duration = 0xFFFF;
        ESP_LOGI(GATTC_TAG, "Enable Ble Scan:during time 0x%04X minutes.",duration);
        esp_ble_gap_start_scanning(duration);
        break;
    }
    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        //scan start complete event to indicate scan start successfully or failed
        if ((err = param->scan_start_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTC_TAG, "Scan start failed: %s", esp_err_to_name(err));
            break;
        }
        ESP_LOGI(GATTC_TAG, "Scan start successed");
        break;
    case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
        if ((err = param->scan_stop_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTC_TAG, "Scan stop failed: %s", esp_err_to_name(err));
            break;
        }
        ESP_LOGI(GATTC_TAG, "Scan stop successed");
        if (is_connect == false) {
            ESP_LOGI(GATTC_TAG, "Connect to the remote device.");
            esp_ble_gattc_open(gl_profile_tab[PROFILE_APP_ID].gattc_if, scan_rst.scan_rst.bda, scan_rst.scan_rst.ble_addr_type, true);
        }
        break;
    case ESP_GAP_BLE_SCAN_RESULT_EVT: {
        esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
        switch (scan_result->scan_rst.search_evt) {
        case ESP_GAP_SEARCH_INQ_RES_EVT:
            esp_log_buffer_hex(GATTC_TAG, scan_result->scan_rst.bda, 6);
            ESP_LOGI(GATTC_TAG, "Searched Adv Data Len %d, Scan Response Len %d", scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);
            adv_name = esp_ble_resolve_adv_data(scan_result->scan_rst.ble_adv, ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
            ESP_LOGI(GATTC_TAG, "Searched Device Name Len %d", adv_name_len);
            esp_log_buffer_char(GATTC_TAG, adv_name, adv_name_len);
            ESP_LOGI(GATTC_TAG, "\n");
            if (adv_name != NULL) {
                if ( strncmp((char *)adv_name, device_name, adv_name_len) == 0) {
                    memcpy(&(scan_rst), scan_result, sizeof(esp_ble_gap_cb_param_t));
                    esp_ble_gap_stop_scanning();
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
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        if ((err = param->adv_stop_cmpl.status) != ESP_BT_STATUS_SUCCESS){
            ESP_LOGE(GATTC_TAG, "Adv stop failed: %s", esp_err_to_name(err));
        }else {
            ESP_LOGI(GATTC_TAG, "Stop adv successfully");
        }
        break;
    default:
        break;
    }
}