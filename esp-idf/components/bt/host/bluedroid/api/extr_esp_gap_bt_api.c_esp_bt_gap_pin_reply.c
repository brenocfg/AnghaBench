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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_bt_pin_code_t ;
typedef  int /*<<< orphan*/  esp_bd_addr_t ;
struct TYPE_9__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_3__ btc_msg_t ;
struct TYPE_7__ {int /*<<< orphan*/  address; } ;
struct TYPE_8__ {int accept; int pin_code_len; int /*<<< orphan*/  pin_code; TYPE_1__ bda; } ;
struct TYPE_10__ {TYPE_2__ pin_reply; } ;
typedef  TYPE_4__ btc_gap_bt_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GAP_BT_ACT_PIN_REPLY ; 
 int /*<<< orphan*/  BTC_PID_GAP_BT ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_gap_bt_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_3__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_bluedroid_get_status () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_bt_gap_pin_reply(esp_bd_addr_t bd_addr, bool accept, uint8_t pin_code_len, esp_bt_pin_code_t pin_code)
{
    btc_msg_t msg;
    btc_gap_bt_args_t arg;

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GAP_BT;
    msg.act = BTC_GAP_BT_ACT_PIN_REPLY;
    arg.pin_reply.accept = accept;
    arg.pin_reply.pin_code_len = pin_code_len;
    memcpy(arg.pin_reply.bda.address, bd_addr, sizeof(esp_bd_addr_t));
    memcpy(arg.pin_reply.pin_code, pin_code, pin_code_len);

    return (btc_transfer_context(&msg, &arg, sizeof(btc_gap_bt_args_t), btc_gap_bt_arg_deep_copy)
            == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}