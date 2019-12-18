#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  future_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_1__ btc_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_MAIN_ACT_DISABLE ; 
 int /*<<< orphan*/  BTC_MAIN_DISABLE_FUTURE ; 
 int /*<<< orphan*/  BTC_PID_MAIN_INIT ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ FUTURE_FAIL ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int bd_already_enable ; 
 int /*<<< orphan*/ ** btc_main_get_future_p (int /*<<< orphan*/ ) ; 
 scalar_t__ btc_transfer_context (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ future_await (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * future_new () ; 

esp_err_t esp_bluedroid_disable(void)
{
    btc_msg_t msg;
    future_t **future_p;

    if (!bd_already_enable) {
        LOG_ERROR("Bluedroid already disabled\n");
        return ESP_ERR_INVALID_STATE;
    }

    future_p = btc_main_get_future_p(BTC_MAIN_DISABLE_FUTURE);
    *future_p = future_new();
    if (*future_p == NULL) {
        LOG_ERROR("Bluedroid disable failed\n");
        return ESP_ERR_NO_MEM;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_MAIN_INIT;
    msg.act = BTC_MAIN_ACT_DISABLE;

    if (btc_transfer_context(&msg, NULL, 0, NULL) != BT_STATUS_SUCCESS) {
        LOG_ERROR("Bluedroid disable failed\n");
        return ESP_FAIL;
    }

    if (future_await(*future_p) == FUTURE_FAIL) {
        LOG_ERROR("Bluedroid disable failed\n");
        return ESP_FAIL;
    }

    bd_already_enable = false;

    return ESP_OK;
}