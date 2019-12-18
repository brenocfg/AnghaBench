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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_msg_ctx_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_4__ {int err_code; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * model; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {TYPE_1__ model_send_comp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ esp_ble_mesh_model_cb_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_SEND_COMP_EVT ; 
 int /*<<< orphan*/  btc_ble_mesh_model_callback (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_ble_mesh_model_send_comp_cb(esp_ble_mesh_model_t *model, esp_ble_mesh_msg_ctx_t *ctx, u32_t opcode, int err)
{
    esp_ble_mesh_model_cb_param_t mesh_param = {0};

    mesh_param.model_send_comp.err_code = err;
    mesh_param.model_send_comp.opcode = opcode;
    mesh_param.model_send_comp.model = model;
    mesh_param.model_send_comp.ctx = ctx;

    btc_ble_mesh_model_callback(&mesh_param, ESP_BLE_MESH_MODEL_SEND_COMP_EVT);
    return;
}