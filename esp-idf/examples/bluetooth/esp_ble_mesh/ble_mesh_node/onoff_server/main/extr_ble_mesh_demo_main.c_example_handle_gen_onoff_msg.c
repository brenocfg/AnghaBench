#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int op_en; int /*<<< orphan*/  onoff; } ;
typedef  TYPE_2__ esp_ble_mesh_server_recv_gen_onoff_set_t ;
struct TYPE_16__ {int recv_op; } ;
typedef  TYPE_3__ esp_ble_mesh_msg_ctx_t ;
struct TYPE_17__ {TYPE_5__* user_data; } ;
typedef  TYPE_4__ esp_ble_mesh_model_t ;
struct TYPE_14__ {int /*<<< orphan*/  onoff; } ;
struct TYPE_18__ {TYPE_1__ state; } ;
typedef  TYPE_5__ esp_ble_mesh_gen_onoff_srv_t ;

/* Variables and functions */
#define  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET 130 
#define  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET 129 
#define  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK 128 
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS ; 
 int /*<<< orphan*/  ROLE_NODE ; 
 int /*<<< orphan*/  esp_ble_mesh_model_publish (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_mesh_server_model_send_msg (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  example_change_led_state (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void example_handle_gen_onoff_msg(esp_ble_mesh_model_t *model,
                                         esp_ble_mesh_msg_ctx_t *ctx,
                                         esp_ble_mesh_server_recv_gen_onoff_set_t *set)
{
    esp_ble_mesh_gen_onoff_srv_t *srv = model->user_data;

    switch (ctx->recv_op) {
    case ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET:
        esp_ble_mesh_server_model_send_msg(model, ctx,
            ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS, sizeof(srv->state.onoff), &srv->state.onoff);
        break;
    case ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET:
    case ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK:
        if (set->op_en == false) {
            srv->state.onoff = set->onoff;
        } else {
            /* TODO: Delay and state transition */
            srv->state.onoff = set->onoff;
        }
        if (ctx->recv_op == ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET) {
            esp_ble_mesh_server_model_send_msg(model, ctx,
                ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS, sizeof(srv->state.onoff), &srv->state.onoff);
        }
        esp_ble_mesh_model_publish(model, ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS,
            sizeof(srv->state.onoff), &srv->state.onoff, ROLE_NODE);
        example_change_led_state(model, ctx, srv->state.onoff);
        break;
    default:
        break;
    }
}