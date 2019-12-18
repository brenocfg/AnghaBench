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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  app_idx; } ;
typedef  TYPE_1__ example_fast_prov_server_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {scalar_t__ user_data; } ;
typedef  TYPE_2__ esp_ble_mesh_model_t ;

/* Variables and functions */
 int /*<<< orphan*/  CID_ESP ; 
 int /*<<< orphan*/  ESP_BLE_MESH_VND_MODEL_ID_FAST_PROV_SRV ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_ble_mesh_get_primary_element_address () ; 
 TYPE_2__* example_find_model (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t example_set_app_idx_to_user_data(uint16_t app_idx)
{
    example_fast_prov_server_t *srv_data = NULL;
    esp_ble_mesh_model_t *srv_model = NULL;

    srv_model = example_find_model(esp_ble_mesh_get_primary_element_address(),
                                   ESP_BLE_MESH_VND_MODEL_ID_FAST_PROV_SRV, CID_ESP);
    if (!srv_model) {
        return ESP_FAIL;
    }

    srv_data = (example_fast_prov_server_t *)(srv_model->user_data);
    if (!srv_data) {
        return ESP_FAIL;
    }

    srv_data->app_idx = app_idx;
    return ESP_OK;
}