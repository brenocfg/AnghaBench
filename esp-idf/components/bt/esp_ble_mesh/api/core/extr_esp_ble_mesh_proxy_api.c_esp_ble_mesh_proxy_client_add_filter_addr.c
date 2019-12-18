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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {scalar_t__* addr; scalar_t__ addr_num; scalar_t__ net_idx; int /*<<< orphan*/  conn_handle; } ;
struct TYPE_8__ {TYPE_1__ proxy_client_add_filter_addr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ btc_ble_mesh_prov_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_MESH_ACT_PROXY_CLIENT_ADD_FILTER_ADDR ; 
 int /*<<< orphan*/  BTC_PID_PROV ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_ble_mesh_prov_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

esp_err_t esp_ble_mesh_proxy_client_add_filter_addr(uint8_t conn_handle,
        uint16_t net_idx, uint16_t *addr, uint16_t addr_num)
{
    btc_ble_mesh_prov_args_t arg = {0};
    btc_msg_t msg = {0};

    if (!addr || addr_num == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_BLE_HOST_STATUS_CHECK(ESP_BLE_HOST_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROXY_CLIENT_ADD_FILTER_ADDR;

    arg.proxy_client_add_filter_addr.conn_handle = conn_handle;
    arg.proxy_client_add_filter_addr.net_idx = net_idx;
    arg.proxy_client_add_filter_addr.addr_num = addr_num;
    arg.proxy_client_add_filter_addr.addr = addr;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), btc_ble_mesh_prov_arg_deep_copy)
            == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}