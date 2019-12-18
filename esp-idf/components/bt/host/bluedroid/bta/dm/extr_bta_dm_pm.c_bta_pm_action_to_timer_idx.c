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
typedef  int UINT8 ;

/* Variables and functions */
 int BTA_DM_PM_MODE_TIMER_MAX ; 
 int BTA_DM_PM_PARK ; 
 int BTA_DM_PM_PARK_TIMER_IDX ; 
 int BTA_DM_PM_SNIFF ; 
 int BTA_DM_PM_SNIFF_TIMER_IDX ; 
 int BTA_DM_PM_SUSPEND ; 
 int BTA_DM_PM_SUSPEND_TIMER_IDX ; 

__attribute__((used)) static UINT8 bta_pm_action_to_timer_idx(UINT8 pm_action)
{
    if (pm_action == BTA_DM_PM_SUSPEND) {
        return BTA_DM_PM_SUSPEND_TIMER_IDX;
    } else if (pm_action == BTA_DM_PM_PARK) {
        return BTA_DM_PM_PARK_TIMER_IDX;
    } else if ((pm_action & BTA_DM_PM_SNIFF) == BTA_DM_PM_SNIFF) {
        return BTA_DM_PM_SNIFF_TIMER_IDX;
    }

    /* Active, no preference, no action and retry */
    return BTA_DM_PM_MODE_TIMER_MAX;
}