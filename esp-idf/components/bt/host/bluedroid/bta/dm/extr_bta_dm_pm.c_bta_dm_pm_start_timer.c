#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* srvc_id; size_t* pm_action; TYPE_2__* timer; int /*<<< orphan*/  active; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ tBTA_PM_TIMER ;
typedef  size_t UINT8 ;
struct TYPE_5__ {int /*<<< orphan*/  p_cback; } ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 scalar_t__ BTA_ID_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_dm_pm_timer_cback ; 
 int /*<<< orphan*/  bta_sys_start_timer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_dm_pm_start_timer(tBTA_PM_TIMER *p_timer, UINT8 timer_idx,
                                  INT32 timeout, UINT8 srvc_id, UINT8 pm_action)
{
    p_timer->in_use = TRUE;
    p_timer->timer[timer_idx].p_cback = bta_dm_pm_timer_cback;

    if (p_timer->srvc_id[timer_idx] == BTA_ID_MAX) {
        p_timer->active++;
    }

    if (p_timer->pm_action[timer_idx] < pm_action) {
        p_timer->pm_action[timer_idx] = pm_action;
    }

    p_timer->srvc_id[timer_idx] = srvc_id;

    bta_sys_start_timer(&p_timer->timer[timer_idx], 0, timeout);
}