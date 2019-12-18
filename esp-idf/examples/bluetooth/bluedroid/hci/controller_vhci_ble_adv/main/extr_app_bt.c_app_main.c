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
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  esp_bt_controller_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONTROLLER_INIT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  ESP_BT_MODE_BLE ; 
 int /*<<< orphan*/  ESP_BT_MODE_CLASSIC_BT ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (scalar_t__) ; 
 scalar_t__ ESP_ERR_NVS_NEW_VERSION_FOUND ; 
 scalar_t__ ESP_ERR_NVS_NO_FREE_PAGES ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  bleAdvtTask ; 
 scalar_t__ esp_bt_controller_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_bt_controller_init (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_bt_controller_mem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_err_to_name (scalar_t__) ; 
 scalar_t__ nvs_flash_erase () ; 
 scalar_t__ nvs_flash_init () ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void app_main(void)
{
    /* Initialize NVS — it is used to store PHY calibration data */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    
    ret = esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
    if (ret) {
        ESP_LOGI(tag, "Bluetooth controller release classic bt memory failed: %s", esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGI(tag, "Bluetooth controller initialize failed: %s", esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_BLE)) != ESP_OK) {
        ESP_LOGI(tag, "Bluetooth controller enable failed: %s", esp_err_to_name(ret));
        return;
    }

    /*
     * If call mem release here, also work. Input ESP_BT_MODE_CLASSIC_BT, the function will
     * release the memory of classic bt mode.
     * esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
     *
     */

    /*
     * If call mem release here, also work. Input ESP_BT_MODE_BTDM, the function will calculate
     * that the BLE mode is already used, so it will release of only classic bt mode.
     * esp_bt_controller_mem_release(ESP_BT_MODE_BTDM);
     */

    xTaskCreatePinnedToCore(&bleAdvtTask, "bleAdvtTask", 2048, NULL, 5, NULL, 0);
}