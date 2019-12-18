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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;

/* Variables and functions */
#define  ESP_BLE_MESH_MODEL_ID_CONFIG_CLI 133 
#define  ESP_BLE_MESH_MODEL_ID_CONFIG_SRV 132 
#define  ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI 131 
#define  ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV 130 
#define  ESP_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI 129 
#define  ESP_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV 128 
 int /*<<< orphan*/ * config_server_models ; 
 int /*<<< orphan*/ * gen_onoff_cli_models ; 
 int /*<<< orphan*/ * gen_onoff_srv_models ; 
 int /*<<< orphan*/ * test_perf_cli_models ; 
 int /*<<< orphan*/ * test_perf_srv_models ; 

esp_ble_mesh_model_t *ble_mesh_get_model(uint16_t model_id)
{
    esp_ble_mesh_model_t *model = NULL;

    switch (model_id) {
    case ESP_BLE_MESH_MODEL_ID_CONFIG_SRV:
        model = config_server_models;
        break;
#if (CONFIG_BLE_MESH_CFG_CLI)
    case ESP_BLE_MESH_MODEL_ID_CONFIG_CLI:
        model = &gen_onoff_cli_models[1];
        break;
#endif
    case ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV:
        model = &gen_onoff_srv_models[1];
        break;
#if (CONFIG_BLE_MESH_GENERIC_ONOFF_CLI)
    case ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI:
        model = &gen_onoff_cli_models[2];
        break;
#endif
    case ESP_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI:
        model = &test_perf_cli_models[0];
        break;
    case ESP_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV:
        model = &test_perf_srv_models[0];
        break;
    }

    return model;
}