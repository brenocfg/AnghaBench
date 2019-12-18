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
 int /*<<< orphan*/  BTC_MAIN_ACT_INIT ; 
 int /*<<< orphan*/  BTC_MAIN_INIT_FUTURE ; 
 int /*<<< orphan*/  BTC_PID_MAIN_INIT ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BT_CONTROLLER_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ FUTURE_FAIL ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int bd_already_init ; 
 int /*<<< orphan*/  btc_init () ; 
 int /*<<< orphan*/ ** btc_main_get_future_p (int /*<<< orphan*/ ) ; 
 scalar_t__ btc_transfer_context (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_bt_controller_get_status () ; 
 scalar_t__ future_await (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * future_new () ; 
 int /*<<< orphan*/  osi_mem_dbg_init () ; 

esp_err_t esp_bluedroid_init(void)
{
    btc_msg_t msg;
    future_t **future_p;

    if (esp_bt_controller_get_status() != ESP_BT_CONTROLLER_STATUS_ENABLED) {
        LOG_ERROR("Controller not initialised\n");
        return ESP_ERR_INVALID_STATE;
    }

    if (bd_already_init) {
        LOG_ERROR("Bluedroid already initialised\n");
        return ESP_ERR_INVALID_STATE;
    }

#if HEAP_MEMORY_DEBUG
    osi_mem_dbg_init();
#endif

    btc_init();

    future_p = btc_main_get_future_p(BTC_MAIN_INIT_FUTURE);
    *future_p = future_new();
    if (*future_p == NULL) {
        LOG_ERROR("Bluedroid initialise failed\n");
        return ESP_ERR_NO_MEM;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_MAIN_INIT;
    msg.act = BTC_MAIN_ACT_INIT;

    if (btc_transfer_context(&msg, NULL, 0, NULL) != BT_STATUS_SUCCESS) {
        LOG_ERROR("Bluedroid initialise failed\n");
        return ESP_FAIL;
    }

    if (future_await(*future_p) == FUTURE_FAIL) {
        LOG_ERROR("Bluedroid initialise failed\n");
        return ESP_FAIL;
    }

    bd_already_init = true;

    return ESP_OK;
}