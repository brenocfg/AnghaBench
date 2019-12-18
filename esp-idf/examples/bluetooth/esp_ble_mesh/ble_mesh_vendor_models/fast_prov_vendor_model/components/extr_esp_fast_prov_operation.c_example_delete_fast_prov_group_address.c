#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {scalar_t__* groups; } ;
typedef  TYPE_1__ esp_ble_mesh_model_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_elem_t ;
struct TYPE_6__ {int element_count; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_2__ esp_ble_mesh_comp_t ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  ESP_BLE_MESH_ADDR_IS_GROUP (scalar_t__) ; 
 scalar_t__ ESP_BLE_MESH_ADDR_UNASSIGNED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_1__* esp_ble_mesh_find_sig_model (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* esp_ble_mesh_get_composition_data () ; 

esp_err_t example_delete_fast_prov_group_address(uint16_t model_id, uint16_t group_addr)
{
    const esp_ble_mesh_comp_t *comp = NULL;
    esp_ble_mesh_elem_t *element = NULL;
    esp_ble_mesh_model_t *model = NULL;
    int i, j;

    if (!ESP_BLE_MESH_ADDR_IS_GROUP(group_addr)) {
        return ESP_ERR_INVALID_ARG;
    }

    comp = esp_ble_mesh_get_composition_data();
    if (comp == NULL) {
        return ESP_FAIL;
    }

    for (i = 0; i < comp->element_count; i++) {
        element = &comp->elements[i];

        model = esp_ble_mesh_find_sig_model(element, model_id);
        if (model == NULL) {
            continue;
        }
        for (j = 0; j < ARRAY_SIZE(model->groups); j++) {
            if (model->groups[j] == group_addr) {
                model->groups[j] = ESP_BLE_MESH_ADDR_UNASSIGNED;
                break;
            }
        }
    }

    return ESP_OK;
}