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
 int /*<<< orphan*/  btm_ble_resume_bg_conn () ; 
 int /*<<< orphan*/  btm_ble_start_adv () ; 

void btm_resume_wl_activity(tBTM_BLE_WL_STATE wl_state)
{
    btm_ble_resume_bg_conn();
    if (wl_state & BTM_BLE_WL_ADV) {
        btm_ble_start_adv();
    }

}