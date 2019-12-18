#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_10__ {int service_uuid_len; } ;
typedef  TYPE_2__ esp_ble_adv_data_t ;
struct TYPE_11__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_3__ btc_msg_t ;
struct TYPE_9__ {int /*<<< orphan*/  adv_data; } ;
struct TYPE_12__ {TYPE_1__ cfg_adv_data; } ;
typedef  TYPE_4__ btc_ble_gap_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GAP_BLE_ACT_CFG_ADV_DATA ; 
 int /*<<< orphan*/  BTC_PID_GAP_BLE ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_gap_ble_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_3__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

esp_err_t esp_ble_gap_config_adv_data(esp_ble_adv_data_t *adv_data)
{
    btc_msg_t msg;
    btc_ble_gap_args_t arg;

    ESP_BLUEDROID_STATUS_CHECK(ESP_BLUEDROID_STATUS_ENABLED);

    if (adv_data == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (adv_data->service_uuid_len & 0xf) { //not 16*n
        return ESP_ERR_INVALID_ARG;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = BTC_GAP_BLE_ACT_CFG_ADV_DATA;
    memcpy(&arg.cfg_adv_data.adv_data, adv_data, sizeof(esp_ble_adv_data_t));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gap_args_t), btc_gap_ble_arg_deep_copy) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);

}