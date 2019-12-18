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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {scalar_t__ mtu; } ;
struct TYPE_8__ {TYPE_1__ set_mtu; } ;
typedef  TYPE_3__ btc_ble_gatt_com_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GATT_ACT_SET_LOCAL_MTU ; 
 int /*<<< orphan*/  BTC_PID_GATT_COMMON ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 scalar_t__ ESP_GATT_DEF_BLE_MTU_SIZE ; 
 scalar_t__ ESP_GATT_MAX_MTU_SIZE ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 

esp_err_t esp_ble_gatt_set_local_mtu (uint16_t mtu)
{
    btc_msg_t msg;
    btc_ble_gatt_com_args_t arg;

    ESP_BLUEDROID_STATUS_CHECK(ESP_BLUEDROID_STATUS_ENABLED);

    if ((mtu < ESP_GATT_DEF_BLE_MTU_SIZE) || (mtu > ESP_GATT_MAX_MTU_SIZE)) {
        return ESP_ERR_INVALID_SIZE;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATT_COMMON;
    msg.act = BTC_GATT_ACT_SET_LOCAL_MTU;
    arg.set_mtu.mtu = mtu;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gatt_com_args_t), NULL) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}