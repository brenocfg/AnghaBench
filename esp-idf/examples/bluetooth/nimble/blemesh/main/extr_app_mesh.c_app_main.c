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

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (scalar_t__) ; 
 scalar_t__ ESP_ERR_NVS_NEW_VERSION_FOUND ; 
 scalar_t__ ESP_ERR_NVS_NO_FREE_PAGES ; 
 int /*<<< orphan*/  ble_store_config_init () ; 
 int /*<<< orphan*/  ble_svc_gap_init () ; 
 int /*<<< orphan*/  ble_svc_gatt_init () ; 
 int /*<<< orphan*/  blemesh_host_task ; 
 int /*<<< orphan*/  bt_mesh_register_gatt () ; 
 scalar_t__ esp_nimble_hci_and_controller_init () ; 
 int /*<<< orphan*/  nimble_port_freertos_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nimble_port_init () ; 
 scalar_t__ nvs_flash_erase () ; 
 scalar_t__ nvs_flash_init () ; 

void app_main(void)
{
    /* Initialize NVS — it is used to store PHY calibration data */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_nimble_hci_and_controller_init());
    nimble_port_init();

    ble_svc_gap_init();
    ble_svc_gatt_init();

    bt_mesh_register_gatt();
    /* XXX Need to have template for store */
    ble_store_config_init();

    nimble_port_freertos_init(blemesh_host_task);
}