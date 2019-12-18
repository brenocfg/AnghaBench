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
 int ESP_BLE_MESH_PROV_ADV ; 
 int ESP_BLE_MESH_PROV_GATT ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LED_G ; 
 int /*<<< orphan*/  LED_ON ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  board_led_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  composition ; 
 scalar_t__ esp_ble_mesh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_mesh_node_prov_enable (int) ; 
 int /*<<< orphan*/  esp_ble_mesh_register_config_server_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_mesh_register_generic_server_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_mesh_register_prov_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  example_ble_mesh_config_server_cb ; 
 int /*<<< orphan*/  example_ble_mesh_generic_server_cb ; 
 int /*<<< orphan*/  example_ble_mesh_provisioning_cb ; 
 int /*<<< orphan*/  provision ; 

__attribute__((used)) static esp_err_t ble_mesh_init(void)
{
    esp_err_t err;

    esp_ble_mesh_register_prov_callback(example_ble_mesh_provisioning_cb);
    esp_ble_mesh_register_config_server_callback(example_ble_mesh_config_server_cb);
    esp_ble_mesh_register_generic_server_callback(example_ble_mesh_generic_server_cb);

    err = esp_ble_mesh_init(&provision, &composition);
    if (err) {
        ESP_LOGE(TAG, "Initializing mesh failed (err %d)", err);
        return err;
    }

    esp_ble_mesh_node_prov_enable(ESP_BLE_MESH_PROV_ADV | ESP_BLE_MESH_PROV_GATT);

    ESP_LOGI(TAG, "BLE Mesh Node initialized");

    board_led_operation(LED_G, LED_ON);

    return err;
}