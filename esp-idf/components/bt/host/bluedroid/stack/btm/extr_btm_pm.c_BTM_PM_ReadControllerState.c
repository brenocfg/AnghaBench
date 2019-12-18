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
typedef  int /*<<< orphan*/  tBTM_CONTRL_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CONTRL_ACTIVE ; 
 int /*<<< orphan*/  BTM_CONTRL_IDLE ; 
 int /*<<< orphan*/  BTM_CONTRL_SCAN ; 
 scalar_t__ TRUE ; 
 scalar_t__ btm_pm_device_in_active_or_sniff_mode () ; 
 scalar_t__ btm_pm_device_in_scan_state () ; 

tBTM_CONTRL_STATE BTM_PM_ReadControllerState(void)
{
    if (TRUE == btm_pm_device_in_active_or_sniff_mode()) {
        return BTM_CONTRL_ACTIVE;
    } else if (TRUE == btm_pm_device_in_scan_state()) {
        return BTM_CONTRL_SCAN;
    } else {
        return BTM_CONTRL_IDLE;
    }
}