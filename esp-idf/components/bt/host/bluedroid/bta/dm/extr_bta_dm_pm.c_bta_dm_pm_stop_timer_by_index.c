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
struct TYPE_3__ {scalar_t__* srvc_id; scalar_t__ active; scalar_t__ in_use; int /*<<< orphan*/ * timer; } ;
typedef  TYPE_1__ tBTA_PM_TIMER ;
typedef  size_t UINT8 ;

/* Variables and functions */
 size_t BTA_DM_PM_MODE_TIMER_MAX ; 
 scalar_t__ BTA_ID_MAX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bta_sys_stop_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_dm_pm_stop_timer_by_index(tBTA_PM_TIMER *p_timer,
        UINT8 timer_idx)
{
    if ((p_timer == NULL) || (timer_idx >= BTA_DM_PM_MODE_TIMER_MAX)) {
        return;
    }

    if (p_timer->srvc_id[timer_idx] == BTA_ID_MAX) {
        return;    /* The timer was not scheduled */
    }

    assert(p_timer->in_use && (p_timer->active > 0));

    bta_sys_stop_timer(&p_timer->timer[timer_idx]);
    p_timer->srvc_id[timer_idx] = BTA_ID_MAX;
    /* NOTE: pm_action[timer_idx] intentionally not reset */

    p_timer->active--;
    if (p_timer->active == 0) {
        p_timer->in_use = FALSE;
    }
}