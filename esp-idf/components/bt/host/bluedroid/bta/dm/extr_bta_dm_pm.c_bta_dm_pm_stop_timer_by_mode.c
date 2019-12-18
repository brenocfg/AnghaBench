#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {TYPE_1__* pm_timer; } ;
struct TYPE_3__ {scalar_t__* srvc_id; scalar_t__* pm_action; int /*<<< orphan*/  peer_bdaddr; scalar_t__ in_use; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int BTA_DM_NUM_PM_TIMER ; 
 scalar_t__ const BTA_DM_PM_MODE_TIMER_MAX ; 
 scalar_t__ BTA_ID_MAX ; 
 int /*<<< orphan*/  bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_pm_stop_timer_by_index (TYPE_1__*,scalar_t__ const) ; 
 scalar_t__ bta_pm_action_to_timer_idx (scalar_t__) ; 

__attribute__((used)) static void bta_dm_pm_stop_timer_by_mode(BD_ADDR peer_addr, UINT8 power_mode)
{
    const UINT8 timer_idx = bta_pm_action_to_timer_idx(power_mode);
    if (timer_idx == BTA_DM_PM_MODE_TIMER_MAX) {
        return;
    }

    for (int i = 0; i < BTA_DM_NUM_PM_TIMER; i++) {
        if (bta_dm_cb.pm_timer[i].in_use && !bdcmp(bta_dm_cb.pm_timer[i].peer_bdaddr, peer_addr)) {
            if (bta_dm_cb.pm_timer[i].srvc_id[timer_idx] != BTA_ID_MAX) {
                bta_dm_pm_stop_timer_by_index(&bta_dm_cb.pm_timer[i], timer_idx);
                /*
                 * TODO: Intentionally setting pm_action[timer_idx].
                 * This assignment should be eliminated in the future - see the
                 * pm_action[] related comment inside function
                 * bta_dm_pm_stop_timer().
                 */
                bta_dm_cb.pm_timer[i].pm_action[timer_idx] = power_mode;
            }
            break;
        }
    }
}