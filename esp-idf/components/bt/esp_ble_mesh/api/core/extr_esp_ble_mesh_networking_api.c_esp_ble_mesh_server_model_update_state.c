#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_server_state_value_t ;
typedef  scalar_t__ esp_ble_mesh_server_state_type_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {int /*<<< orphan*/ * value; scalar_t__ type; int /*<<< orphan*/ * model; } ;
struct TYPE_8__ {TYPE_1__ model_update_state; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ btc_ble_mesh_model_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_MESH_ACT_SERVER_MODEL_UPDATE_STATE ; 
 int /*<<< orphan*/  BTC_PID_MODEL ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_ENABLED ; 
 scalar_t__ ESP_BLE_MESH_SERVER_MODEL_STATE_MAX ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_ble_mesh_model_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

esp_err_t esp_ble_mesh_server_model_update_state(esp_ble_mesh_model_t *model,
        esp_ble_mesh_server_state_type_t type,
        esp_ble_mesh_server_state_value_t *value)
{
    btc_ble_mesh_model_args_t arg = {0};
    btc_msg_t msg = {0};

    if (!model || !value || type >= ESP_BLE_MESH_SERVER_MODEL_STATE_MAX) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_BLE_HOST_STATUS_CHECK(ESP_BLE_HOST_STATUS_ENABLED);

    arg.model_update_state.model = model;
    arg.model_update_state.type = type;
    arg.model_update_state.value = value;

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_MODEL;
    msg.act = BTC_BLE_MESH_ACT_SERVER_MODEL_UPDATE_STATE;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_model_args_t), btc_ble_mesh_model_arg_deep_copy)
            == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}