#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  role; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dst; int /*<<< orphan*/  net_idx; int /*<<< orphan*/  app_idx; } ;
typedef  TYPE_3__ example_msg_common_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_12__ {int app_idx; int send_rel; scalar_t__ send_ttl; int /*<<< orphan*/  addr; int /*<<< orphan*/  net_idx; } ;
struct TYPE_14__ {int /*<<< orphan*/  msg_role; int /*<<< orphan*/  msg_timeout; TYPE_2__ ctx; int /*<<< orphan*/ * model; int /*<<< orphan*/  opcode; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ esp_ble_mesh_client_common_param_t ;
struct TYPE_11__ {int /*<<< orphan*/  app_key; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
struct TYPE_15__ {TYPE_1__ app_key_add; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ esp_ble_mesh_cfg_client_set_state_t ;
struct TYPE_16__ {int /*<<< orphan*/  const* app_key; int /*<<< orphan*/  app_idx; int /*<<< orphan*/  net_idx; } ;
typedef  TYPE_6__ esp_ble_mesh_cfg_app_key_add_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BLE_MESH_MODEL_OP_APP_KEY_ADD ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  esp_ble_mesh_config_client_set_state (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * esp_ble_mesh_get_fast_prov_app_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

esp_err_t example_send_config_appkey_add(esp_ble_mesh_model_t *model,
        example_msg_common_info_t *info,
        esp_ble_mesh_cfg_app_key_add_t *add_key)
{
    esp_ble_mesh_client_common_param_t common = {0};
    esp_ble_mesh_cfg_client_set_state_t set = {0};
    const uint8_t *key = NULL;

    if (!model || !info) {
        return ESP_ERR_INVALID_ARG;
    }

    if (add_key) {
        set.app_key_add.net_idx = add_key->net_idx;
        set.app_key_add.app_idx = add_key->app_idx;
        memcpy(set.app_key_add.app_key, add_key->app_key, 16);
    } else {
#if defined(CONFIG_BLE_MESH_FAST_PROV)
        key = esp_ble_mesh_get_fast_prov_app_key(info->net_idx, info->app_idx);
#endif
        if (!key) {
            return ESP_FAIL;
        }
        set.app_key_add.net_idx = info->net_idx;
        set.app_key_add.app_idx = info->app_idx;
        memcpy(set.app_key_add.app_key, key, 16);
    }

    common.opcode       = ESP_BLE_MESH_MODEL_OP_APP_KEY_ADD;
    common.model        = model;
    common.ctx.net_idx  = info->net_idx;
    common.ctx.app_idx  = 0x0000; /* not used for config messages */
    common.ctx.addr     = info->dst;
    common.ctx.send_rel = false;
    common.ctx.send_ttl = 0;
    common.msg_timeout  = info->timeout;
    common.msg_role     = info->role;

    return esp_ble_mesh_config_client_set_state(&common, &set);
}