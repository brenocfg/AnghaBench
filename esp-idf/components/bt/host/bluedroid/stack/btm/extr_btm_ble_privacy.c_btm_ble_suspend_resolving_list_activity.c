#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ adv_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  suspended_rl_state; int /*<<< orphan*/  scan_activity; TYPE_1__ inq_var; } ;
typedef  TYPE_2__ tBTM_BLE_CB ;
struct TYPE_6__ {TYPE_2__ ble_ctr_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BLE_DIR_CONN ; 
 scalar_t__ BTM_BLE_ADV_ENABLE ; 
 scalar_t__ BTM_BLE_IS_SCAN_ACTIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_BLE_RL_ADV ; 
 int /*<<< orphan*/  BTM_BLE_RL_IDLE ; 
 int /*<<< orphan*/  BTM_BLE_RL_INIT ; 
 int /*<<< orphan*/  BTM_BLE_RL_SCAN ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ btm_ble_get_conn_st () ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 
 int /*<<< orphan*/  btm_ble_stop_scan () ; 
 scalar_t__ btm_ble_suspend_bg_conn () ; 
 TYPE_3__ btm_cb ; 

BOOLEAN btm_ble_suspend_resolving_list_activity(void)
{
    tBTM_BLE_CB *p_ble_cb = &btm_cb.ble_ctr_cb;

    /* if resolving list is not enabled, do not need to terminate any activity */
    /* if asking for stop all activity */
    /* if already suspended */
    if (p_ble_cb->suspended_rl_state != BTM_BLE_RL_IDLE) {
        return TRUE;
    }

    /* direct connection active, wait until it completed */
    if (btm_ble_get_conn_st() == BLE_DIR_CONN) {
        BTM_TRACE_ERROR("resolving list can not be edited, EnQ now");
        return FALSE;
    }

    p_ble_cb->suspended_rl_state = BTM_BLE_RL_IDLE;

    if (p_ble_cb->inq_var.adv_mode == BTM_BLE_ADV_ENABLE) {
        btm_ble_stop_adv();
        p_ble_cb->suspended_rl_state |= BTM_BLE_RL_ADV;
    }

    if (BTM_BLE_IS_SCAN_ACTIVE(p_ble_cb->scan_activity)) {
        btm_ble_stop_scan();
        p_ble_cb->suspended_rl_state |= BTM_BLE_RL_SCAN;
    }

    if (btm_ble_suspend_bg_conn()) {
        p_ble_cb->suspended_rl_state |= BTM_BLE_RL_INIT;
    }

    return TRUE;
}