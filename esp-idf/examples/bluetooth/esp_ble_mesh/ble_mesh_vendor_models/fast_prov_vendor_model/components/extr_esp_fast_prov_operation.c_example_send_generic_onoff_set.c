#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  role; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dst; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
typedef  TYPE_3__ example_msg_common_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_9__ {int op_en; void* tid; void* onoff; } ;
struct TYPE_12__ {TYPE_1__ onoff_set; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ esp_ble_mesh_generic_client_set_state_t ;
struct TYPE_10__ {int send_rel; scalar_t__ send_ttl; int /*<<< orphan*/  addr; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
struct TYPE_13__ {int /*<<< orphan*/  msg_role; int /*<<< orphan*/  msg_timeout; TYPE_2__ ctx; int /*<<< orphan*/ * model; int /*<<< orphan*/  opcode; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ esp_ble_mesh_client_common_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET ; 
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  esp_ble_mesh_generic_client_set_state (TYPE_5__*,TYPE_4__*) ; 

esp_err_t example_send_generic_onoff_set(esp_ble_mesh_model_t *model,
        example_msg_common_info_t *info,
        uint8_t onoff, uint8_t tid, bool need_ack)
{
    esp_ble_mesh_generic_client_set_state_t set = {0};
    esp_ble_mesh_client_common_param_t common = {0};

    if (!model || !info) {
        return ESP_ERR_INVALID_ARG;
    }

    set.onoff_set.onoff = onoff;
    set.onoff_set.tid   = tid;
    set.onoff_set.op_en = false;

    if (need_ack) {
        common.opcode = ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET;
    } else {
        common.opcode = ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK;
    }
    common.model        = model;
    common.ctx.net_idx  = info->net_idx;
    common.ctx.app_idx  = info->app_idx;
    common.ctx.addr     = info->dst;
    common.ctx.send_rel = false;
    common.ctx.send_ttl = 0;
    common.msg_timeout  = info->timeout;
    common.msg_role     = info->role;

    return esp_ble_mesh_generic_client_set_state(&common, &set);
}