#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int esp_gap_ble_cb_event_t ;
typedef  int /*<<< orphan*/  esp_ble_gap_cb_param_t ;
struct TYPE_2__ {int /*<<< orphan*/  adv_params; } ;

/* Variables and functions */
#define  ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT 129 
#define  ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT 128 
 int /*<<< orphan*/  adv_config_done ; 
 int /*<<< orphan*/  adv_config_flag ; 
 int /*<<< orphan*/  esp_ble_gap_start_advertising (int /*<<< orphan*/ *) ; 
 TYPE_1__* g_ble_cfg_p ; 
 int /*<<< orphan*/  scan_rsp_config_flag ; 

__attribute__((used)) static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        adv_config_done &= (~adv_config_flag);
        if (adv_config_done == 0) {
            esp_ble_gap_start_advertising(&g_ble_cfg_p->adv_params);
        }
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
        adv_config_done &= (~scan_rsp_config_flag);
        if (adv_config_done == 0) {
            esp_ble_gap_start_advertising(&g_ble_cfg_p->adv_params);
        }
        break;
    default:
        break;
    }
}