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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  bta_sys_get_remaining_ticks (int /*<<< orphan*/ *) ; 

UINT32 bta_dm_pm_get_remaining_ticks (TIMER_LIST_ENT  *p_target_tle)
{
    return bta_sys_get_remaining_ticks(p_target_tle);
}