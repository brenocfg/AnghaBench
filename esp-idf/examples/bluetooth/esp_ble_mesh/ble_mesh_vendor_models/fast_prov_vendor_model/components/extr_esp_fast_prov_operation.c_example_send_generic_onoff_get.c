#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  role; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dst; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
typedef  TYPE_2__ example_msg_common_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ esp_ble_mesh_generic_client_get_state_t ;
struct TYPE_8__ {int send_rel; scalar_t__ send_ttl; int /*<<< orphan*/  addr; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
struct TYPE_11__ {int /*<<< orphan*/  msg_role; int /*<<< orphan*/  msg_timeout; TYPE_1__ ctx; int /*<<< orphan*/ * model; int /*<<< orphan*/  opcode; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ esp_ble_mesh_client_common_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  esp_ble_mesh_generic_client_get_state (TYPE_4__*,TYPE_3__*) ; 

esp_err_t example_send_generic_onoff_get(esp_ble_mesh_model_t *model,
        example_msg_common_info_t *info)
{
    esp_ble_mesh_generic_client_get_state_t get = {0};
    esp_ble_mesh_client_common_param_t common = {0};

    if (!model || !info) {
        return ESP_ERR_INVALID_ARG;
    }

    common.opcode       = ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET;
    common.model        = model;
    common.ctx.net_idx  = info->net_idx;
    common.ctx.app_idx  = info->app_idx;
    common.ctx.addr     = info->dst;
    common.ctx.send_rel = false;
    common.ctx.send_ttl = 0;
    common.msg_timeout  = info->timeout;
    common.msg_role     = info->role;

    return esp_ble_mesh_generic_client_get_state(&common, &get);
}