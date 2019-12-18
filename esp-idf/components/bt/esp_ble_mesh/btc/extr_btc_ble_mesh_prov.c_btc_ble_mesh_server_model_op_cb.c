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
struct net_buf_simple {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct bt_mesh_msg_ctx {int /*<<< orphan*/  recv_op; } ;
struct bt_mesh_model {int dummy; } ;
typedef  int /*<<< orphan*/  esp_ble_mesh_msg_ctx_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_4__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  length; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * model; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {TYPE_1__ model_operation; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ esp_ble_mesh_model_cb_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OPERATION_EVT ; 
 int /*<<< orphan*/  btc_ble_mesh_model_callback (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_ble_mesh_server_model_op_cb(struct bt_mesh_model *model,
        struct bt_mesh_msg_ctx *ctx,
        struct net_buf_simple *buf)
{
    esp_ble_mesh_model_cb_param_t mesh_param = {0};

    mesh_param.model_operation.opcode = ctx->recv_op;
    mesh_param.model_operation.model = (esp_ble_mesh_model_t *)model;
    mesh_param.model_operation.ctx = (esp_ble_mesh_msg_ctx_t *)ctx;
    mesh_param.model_operation.length = buf->len;
    mesh_param.model_operation.msg = buf->data;

    btc_ble_mesh_model_callback(&mesh_param, ESP_BLE_MESH_MODEL_OPERATION_EVT);
    return;
}