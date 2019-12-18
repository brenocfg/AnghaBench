#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int tBTM_BLE_WL_STATE ;

/* Variables and functions */
 int BTM_BLE_WL_ADV ; 
 int BTM_BLE_WL_INIT ; 
 int BTM_BLE_WL_SCAN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  btm_ble_start_auto_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_start_select_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 

__attribute__((used)) static void btm_suspend_wl_activity(tBTM_BLE_WL_STATE wl_state)
{
    if (wl_state & BTM_BLE_WL_INIT) {
        btm_ble_start_auto_conn(FALSE);
    }
    if (wl_state & BTM_BLE_WL_SCAN) {
        btm_ble_start_select_conn(FALSE, NULL);
    }
    if (wl_state & BTM_BLE_WL_ADV) {
        btm_ble_stop_adv();
    }

}