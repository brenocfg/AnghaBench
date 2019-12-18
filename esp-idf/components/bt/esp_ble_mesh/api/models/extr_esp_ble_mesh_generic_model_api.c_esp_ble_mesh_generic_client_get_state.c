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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_generic_client_get_state_t ;
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {TYPE_2__ ctx; int /*<<< orphan*/  model; } ;
typedef  TYPE_3__ esp_ble_mesh_client_common_param_t ;
struct TYPE_12__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ btc_msg_t ;
struct TYPE_9__ {int /*<<< orphan*/ * get_state; TYPE_3__* params; } ;
struct TYPE_13__ {TYPE_1__ generic_client_get_state; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ btc_ble_mesh_generic_client_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_MESH_ACT_GENERIC_CLIENT_GET_STATE ; 
 int /*<<< orphan*/  BTC_PID_GENERIC_CLIENT ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_ble_mesh_generic_client_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_4__*,TYPE_5__*,int,int /*<<< orphan*/ ) ; 

esp_err_t esp_ble_mesh_generic_client_get_state(esp_ble_mesh_client_common_param_t *params,
        esp_ble_mesh_generic_client_get_state_t *get_state)
{
    btc_ble_mesh_generic_client_args_t arg = {0};
    btc_msg_t msg = {0};

    if (!params || !params->model || !params->ctx.addr || !get_state) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_BLE_HOST_STATUS_CHECK(ESP_BLE_HOST_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GENERIC_CLIENT;
    msg.act = BTC_BLE_MESH_ACT_GENERIC_CLIENT_GET_STATE;
    arg.generic_client_get_state.params = params;
    arg.generic_client_get_state.get_state = get_state;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_generic_client_args_t), btc_ble_mesh_generic_client_arg_deep_copy)
            == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}