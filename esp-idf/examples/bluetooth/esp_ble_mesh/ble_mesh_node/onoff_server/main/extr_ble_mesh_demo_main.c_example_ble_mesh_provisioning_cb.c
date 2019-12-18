#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {char* err_code; } ;
struct TYPE_12__ {int /*<<< orphan*/  iv_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  net_idx; } ;
struct TYPE_11__ {int /*<<< orphan*/  bearer; } ;
struct TYPE_10__ {int /*<<< orphan*/  bearer; } ;
struct TYPE_9__ {char* err_code; } ;
struct TYPE_14__ {char* err_code; } ;
struct TYPE_15__ {TYPE_5__ node_set_unprov_dev_name_comp; TYPE_4__ node_prov_complete; TYPE_3__ node_prov_link_close; TYPE_2__ node_prov_link_open; TYPE_1__ node_prov_enable_comp; TYPE_6__ prov_register_comp; } ;
typedef  TYPE_7__ esp_ble_mesh_prov_cb_param_t ;
typedef  int esp_ble_mesh_prov_cb_event_t ;

/* Variables and functions */
#define  ESP_BLE_MESH_NODE_PROV_COMPLETE_EVT 134 
#define  ESP_BLE_MESH_NODE_PROV_ENABLE_COMP_EVT 133 
#define  ESP_BLE_MESH_NODE_PROV_LINK_CLOSE_EVT 132 
#define  ESP_BLE_MESH_NODE_PROV_LINK_OPEN_EVT 131 
#define  ESP_BLE_MESH_NODE_PROV_RESET_EVT 130 
#define  ESP_BLE_MESH_NODE_SET_UNPROV_DEV_NAME_COMP_EVT 129 
 int /*<<< orphan*/  ESP_BLE_MESH_PROV_ADV ; 
#define  ESP_BLE_MESH_PROV_REGISTER_COMP_EVT 128 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  prov_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void example_ble_mesh_provisioning_cb(esp_ble_mesh_prov_cb_event_t event,
                                             esp_ble_mesh_prov_cb_param_t *param)
{
    switch (event) {
    case ESP_BLE_MESH_PROV_REGISTER_COMP_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_PROV_REGISTER_COMP_EVT, err_code %d", param->prov_register_comp.err_code);
        break;
    case ESP_BLE_MESH_NODE_PROV_ENABLE_COMP_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_NODE_PROV_ENABLE_COMP_EVT, err_code %d", param->node_prov_enable_comp.err_code);
        break;
    case ESP_BLE_MESH_NODE_PROV_LINK_OPEN_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_NODE_PROV_LINK_OPEN_EVT, bearer %s",
            param->node_prov_link_open.bearer == ESP_BLE_MESH_PROV_ADV ? "PB-ADV" : "PB-GATT");
        break;
    case ESP_BLE_MESH_NODE_PROV_LINK_CLOSE_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_NODE_PROV_LINK_CLOSE_EVT, bearer %s",
            param->node_prov_link_close.bearer == ESP_BLE_MESH_PROV_ADV ? "PB-ADV" : "PB-GATT");
        break;
    case ESP_BLE_MESH_NODE_PROV_COMPLETE_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_NODE_PROV_COMPLETE_EVT");
        prov_complete(param->node_prov_complete.net_idx, param->node_prov_complete.addr,
            param->node_prov_complete.flags, param->node_prov_complete.iv_index);
        break;
    case ESP_BLE_MESH_NODE_PROV_RESET_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_NODE_PROV_RESET_EVT");
        break;
    case ESP_BLE_MESH_NODE_SET_UNPROV_DEV_NAME_COMP_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_NODE_SET_UNPROV_DEV_NAME_COMP_EVT, err_code %d", param->node_set_unprov_dev_name_comp.err_code);
        break;
    default:
        break;
    }
}