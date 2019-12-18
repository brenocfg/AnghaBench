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
typedef  int esp_gap_ble_cb_event_t ;
typedef  int /*<<< orphan*/  esp_ble_gap_cb_param_t ;

/* Variables and functions */
#define  ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT 128 
 int /*<<< orphan*/  esp_ble_gap_start_advertising (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  example_adv_params ; 

__attribute__((used)) static void example_gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        esp_ble_gap_start_advertising(&example_adv_params);
        break;
    default:
        break;
    }
}