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
typedef  int /*<<< orphan*/  esp_blufi_error_state_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_1__ blufi_err_infor; } ;
typedef  TYPE_3__ btc_blufi_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLUFI_ACT_SEND_ERR_INFO ; 
 int /*<<< orphan*/  BTC_PID_BLUFI ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_bluedroid_get_status () ; 

esp_err_t esp_blufi_send_error_info(esp_blufi_error_state_t state)
{
    btc_msg_t msg;
    btc_blufi_args_t arg;

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_BLUFI;
    msg.act = BTC_BLUFI_ACT_SEND_ERR_INFO;
    arg.blufi_err_infor.state = state;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_blufi_args_t), NULL) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}