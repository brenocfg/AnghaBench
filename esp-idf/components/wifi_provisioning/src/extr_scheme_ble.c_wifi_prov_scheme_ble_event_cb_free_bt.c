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
typedef  int wifi_prov_cb_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BT_MODE_CLASSIC_BT ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
#define  WIFI_PROV_INIT 128 
 int /*<<< orphan*/  esp_bt_mem_release (int /*<<< orphan*/ ) ; 

void wifi_prov_scheme_ble_event_cb_free_bt(void *user_data, wifi_prov_cb_event_t event, void *event_data)
{
    esp_err_t err;
    switch (event) {
        case WIFI_PROV_INIT:
            /* Release BT memory, as we need only BLE */
            err = esp_bt_mem_release(ESP_BT_MODE_CLASSIC_BT);
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "bt_mem_release of classic BT failed %d", err);
            } else {
                ESP_LOGI(TAG, "BT memory released");
            }
            break;

        default:
            break;
    }
}