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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  match ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; int /*<<< orphan*/  app_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_KEY_IDX ; 
 int /*<<< orphan*/  APP_KEY_OCTET ; 
 int /*<<< orphan*/  ESP_BLE_MESH_KEY_PRIMARY ; 
 int ESP_BLE_MESH_PROV_ADV ; 
 int ESP_BLE_MESH_PROV_GATT ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  composition ; 
 scalar_t__ esp_ble_mesh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_mesh_provisioner_add_local_app_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_mesh_provisioner_prov_enable (int) ; 
 int /*<<< orphan*/  esp_ble_mesh_provisioner_set_dev_uuid_match (int*,int,int,int) ; 
 int /*<<< orphan*/  esp_ble_mesh_register_config_client_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_mesh_register_generic_client_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_mesh_register_prov_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  example_ble_mesh_config_client_cb ; 
 int /*<<< orphan*/  example_ble_mesh_generic_client_cb ; 
 int /*<<< orphan*/  example_ble_mesh_provisioning_cb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ prov_key ; 
 int /*<<< orphan*/  provision ; 

__attribute__((used)) static esp_err_t ble_mesh_init(void)
{
    uint8_t match[2] = {0xdd, 0xdd};
    esp_err_t err;

    prov_key.net_idx = ESP_BLE_MESH_KEY_PRIMARY;
    prov_key.app_idx = APP_KEY_IDX;
    memset(prov_key.app_key, APP_KEY_OCTET, sizeof(prov_key.app_key));

    esp_ble_mesh_register_prov_callback(example_ble_mesh_provisioning_cb);
    esp_ble_mesh_register_config_client_callback(example_ble_mesh_config_client_cb);
    esp_ble_mesh_register_generic_client_callback(example_ble_mesh_generic_client_cb);


    err = esp_ble_mesh_init(&provision, &composition);
    if (err) {
        ESP_LOGE(TAG, "Initializing mesh failed (err %d)", err);
        return err;
    }

    esp_ble_mesh_provisioner_set_dev_uuid_match(match, sizeof(match), 0x0, false);

    esp_ble_mesh_provisioner_prov_enable(ESP_BLE_MESH_PROV_ADV | ESP_BLE_MESH_PROV_GATT);

    esp_ble_mesh_provisioner_add_local_app_key(prov_key.app_key, prov_key.net_idx, prov_key.app_idx);

    ESP_LOGI(TAG, "BLE Mesh Provisioner initialized");

    return err;
}