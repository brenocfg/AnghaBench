#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {int /*<<< orphan*/  unicast; } ;
typedef  TYPE_2__ esp_ble_mesh_node_info_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_7__ {int /*<<< orphan*/  send_rel; int /*<<< orphan*/  send_ttl; int /*<<< orphan*/  addr; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
struct TYPE_9__ {int /*<<< orphan*/  msg_role; int /*<<< orphan*/  msg_timeout; TYPE_1__ ctx; int /*<<< orphan*/ * model; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_3__ esp_ble_mesh_client_common_param_t ;
struct TYPE_10__ {int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MSG_ROLE ; 
 int /*<<< orphan*/  MSG_SEND_REL ; 
 int /*<<< orphan*/  MSG_SEND_TTL ; 
 int /*<<< orphan*/  MSG_TIMEOUT ; 
 TYPE_4__ prov_key ; 

__attribute__((used)) static esp_err_t example_ble_mesh_set_msg_common(esp_ble_mesh_client_common_param_t *common,
                                                 esp_ble_mesh_node_info_t *node,
                                                 esp_ble_mesh_model_t *model, uint32_t opcode)
{
    if (!common || !node || !model) {
        return ESP_ERR_INVALID_ARG;
    }

    common->opcode = opcode;
    common->model = model;
    common->ctx.net_idx = prov_key.net_idx;
    common->ctx.app_idx = prov_key.app_idx;
    common->ctx.addr = node->unicast;
    common->ctx.send_ttl = MSG_SEND_TTL;
    common->ctx.send_rel = MSG_SEND_REL;
    common->msg_timeout = MSG_TIMEOUT;
    common->msg_role = MSG_ROLE;

    return ESP_OK;
}