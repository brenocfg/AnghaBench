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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ibeacon_adv_data ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  esp_bt_controller_config_t ;
typedef  int /*<<< orphan*/  esp_ble_ibeacon_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONTROLLER_INIT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  DEMO_TAG ; 
 int /*<<< orphan*/  ESP_BT_MODE_BLE ; 
 int /*<<< orphan*/  ESP_BT_MODE_CLASSIC_BT ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ble_ibeacon_init () ; 
 int /*<<< orphan*/  ble_scan_params ; 
 scalar_t__ esp_ble_config_ibeacon_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gap_config_adv_data_raw (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  esp_ble_gap_set_scan_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_bt_controller_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_controller_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_bt_controller_mem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_err_to_name (scalar_t__) ; 
 int /*<<< orphan*/  nvs_flash_init () ; 
 int /*<<< orphan*/  vendor_config ; 

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);

    ble_ibeacon_init();

    /* set scan parameters */
#if (IBEACON_MODE == IBEACON_RECEIVER)
    esp_ble_gap_set_scan_params(&ble_scan_params);

#elif (IBEACON_MODE == IBEACON_SENDER)
    esp_ble_ibeacon_t ibeacon_adv_data;
    esp_err_t status = esp_ble_config_ibeacon_data (&vendor_config, &ibeacon_adv_data);
    if (status == ESP_OK){
        esp_ble_gap_config_adv_data_raw((uint8_t*)&ibeacon_adv_data, sizeof(ibeacon_adv_data));
    }
    else {
        ESP_LOGE(DEMO_TAG, "Config iBeacon data failed: %s\n", esp_err_to_name(status));
    }
#endif
}