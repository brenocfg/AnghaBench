#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {scalar_t__ manufacturer_len; scalar_t__ url_len; int /*<<< orphan*/ * p_url; int /*<<< orphan*/ * p_manufacturer_data; } ;
typedef  TYPE_1__ esp_bt_eir_data_t ;
struct TYPE_9__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_10__ {int /*<<< orphan*/  config_eir; } ;
typedef  TYPE_3__ btc_gap_bt_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GAP_BT_ACT_CONFIG_EIR ; 
 int /*<<< orphan*/  BTC_PID_GAP_BT ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 scalar_t__ ESP_BT_EIR_MAX_LEN ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_gap_bt_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_bluedroid_get_status () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

esp_err_t esp_bt_gap_config_eir_data(esp_bt_eir_data_t *eir_data)
{
    btc_msg_t msg;
    btc_gap_bt_args_t arg;

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }

    if (eir_data == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (eir_data->manufacturer_len > ESP_BT_EIR_MAX_LEN
        || eir_data->url_len > ESP_BT_EIR_MAX_LEN) {
        return ESP_ERR_INVALID_ARG;
    }

    if ((eir_data->manufacturer_len > 0 && eir_data->p_manufacturer_data == NULL)
        || (eir_data->url_len > 0 && eir_data->p_url == NULL)) {
        return ESP_ERR_INVALID_ARG;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GAP_BT;
    msg.act = BTC_GAP_BT_ACT_CONFIG_EIR;

    memcpy(&arg.config_eir, eir_data, sizeof(esp_bt_eir_data_t));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_gap_bt_args_t), btc_gap_bt_arg_deep_copy) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}