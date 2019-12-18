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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_elem_t ;

/* Variables and functions */
 int /*<<< orphan*/  CID_NVAL ; 
 int /*<<< orphan*/  ESP_BLE_MESH_ADDR_IS_UNICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_ble_mesh_find_element (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_ble_mesh_find_sig_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_ble_mesh_find_vendor_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_ble_mesh_model_t *example_find_model(uint16_t element_addr, uint16_t model_id,
        uint16_t company_id)
{
    esp_ble_mesh_elem_t *element = NULL;

    if (!ESP_BLE_MESH_ADDR_IS_UNICAST(element_addr)) {
        return NULL;
    }

    element = esp_ble_mesh_find_element(element_addr);
    if (!element) {
        return NULL;
    }

    if (company_id == CID_NVAL) {
        return esp_ble_mesh_find_sig_model(element, model_id);
    } else {
        return esp_ble_mesh_find_vendor_model(element, company_id, model_id);
    }
}