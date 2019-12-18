#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  onoff; } ;
struct TYPE_8__ {TYPE_1__ onoff_set; } ;
struct TYPE_9__ {TYPE_2__ state_change; } ;
struct TYPE_10__ {int /*<<< orphan*/  recv_op; int /*<<< orphan*/  recv_dst; int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {TYPE_3__ value; TYPE_4__ ctx; } ;
typedef  TYPE_5__ esp_ble_mesh_generic_server_cb_param_t ;
typedef  int esp_ble_mesh_generic_server_cb_event_t ;

/* Variables and functions */
#define  ESP_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT 128 
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET ; 
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  example_change_led_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void example_ble_mesh_generic_server_cb(esp_ble_mesh_generic_server_cb_event_t event,
                                               esp_ble_mesh_generic_server_cb_param_t *param)
{
    ESP_LOGI(TAG, "event 0x%02x, opcode 0x%04x, src 0x%04x, dst 0x%04x",
        event, param->ctx.recv_op, param->ctx.addr, param->ctx.recv_dst);

    switch (event) {
    case ESP_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT:
        ESP_LOGI(TAG, "ESP_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT");
        if (param->ctx.recv_op == ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET ||
            param->ctx.recv_op == ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK) {
            ESP_LOGI(TAG, "onoff 0x%02x", param->value.state_change.onoff_set.onoff);
            example_change_led_state(param->value.state_change.onoff_set.onoff);
        }
        break;
    default:
        ESP_LOGW(TAG, "Unknown Generic Server event 0x%02x", event);
        break;
    }
}