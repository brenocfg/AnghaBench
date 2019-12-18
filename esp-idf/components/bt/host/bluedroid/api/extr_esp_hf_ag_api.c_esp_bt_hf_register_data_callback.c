#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_hf_outgoing_data_cb_t ;
typedef  int /*<<< orphan*/  esp_hf_incoming_data_cb_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_7__ {int /*<<< orphan*/  send; int /*<<< orphan*/  recv; } ;
struct TYPE_9__ {TYPE_1__ reg_data_cb; } ;
typedef  TYPE_3__ btc_hf_args_t ;
typedef  scalar_t__ bt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_HF_REGISTER_DATA_CALLBACK_EVT ; 
 int /*<<< orphan*/  BTC_PID_HF ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_bluedroid_get_status () ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_bt_hf_register_data_callback(esp_hf_incoming_data_cb_t recv, esp_hf_outgoing_data_cb_t send)
{
    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }
    btc_msg_t msg;
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_HF;
    msg.act = BTC_HF_REGISTER_DATA_CALLBACK_EVT;

    btc_hf_args_t arg;
    memset(&arg, 0, sizeof(btc_hf_args_t));
    arg.reg_data_cb.recv = recv;
    arg.reg_data_cb.send = send;

    /* Switch to BTC context */
    bt_status_t status = btc_transfer_context(&msg, &arg, sizeof(btc_hf_args_t), NULL);
    return (status == BT_STATUS_SUCCESS) ? ESP_OK : ESP_FAIL;
}