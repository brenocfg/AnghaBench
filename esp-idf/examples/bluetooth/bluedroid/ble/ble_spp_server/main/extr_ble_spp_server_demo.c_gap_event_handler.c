#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int esp_gap_ble_cb_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_1__ adv_start_cmpl; } ;
typedef  TYPE_2__ esp_ble_gap_cb_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
#define  ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT 129 
#define  ESP_GAP_BLE_ADV_START_COMPLETE_EVT 128 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GATTS_TABLE_TAG ; 
 int /*<<< orphan*/  esp_ble_gap_start_advertising (int /*<<< orphan*/ *) ; 
 int esp_err_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spp_adv_params ; 

__attribute__((used)) static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    esp_err_t err;
    ESP_LOGE(GATTS_TABLE_TAG, "GAP_EVT, event %d\n", event);

    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        esp_ble_gap_start_advertising(&spp_adv_params);
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if((err = param->adv_start_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTS_TABLE_TAG, "Advertising start failed: %s\n", esp_err_to_name(err));
        }
        break;
    default:
        break;
    }
}