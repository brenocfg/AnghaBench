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
struct TYPE_3__ {scalar_t__* srvc_id; int /*<<< orphan*/ * pm_action; int /*<<< orphan*/  peer_bdaddr; scalar_t__ in_use; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int BTA_DM_NUM_PM_TIMER ; 
 int BTA_DM_PM_MODE_TIMER_MAX ; 
 int /*<<< orphan*/  BTA_DM_PM_NO_ACTION ; 
 int /*<<< orphan*/  bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_pm_stop_timer_by_index (TYPE_1__*,int) ; 

__attribute__((used)) static void bta_dm_pm_stop_timer_by_srvc_id(BD_ADDR peer_addr, UINT8 srvc_id)
{
    for (int i = 0; i < BTA_DM_NUM_PM_TIMER; i++) {
        if (bta_dm_cb.pm_timer[i].in_use && !bdcmp(bta_dm_cb.pm_timer[i].peer_bdaddr, peer_addr)) {
            for (int j = 0; j < BTA_DM_PM_MODE_TIMER_MAX; j++) {
                if (bta_dm_cb.pm_timer[i].srvc_id[j] == srvc_id) {
                    bta_dm_pm_stop_timer_by_index(&bta_dm_cb.pm_timer[i], j);
                    bta_dm_cb.pm_timer[i].pm_action[j] = BTA_DM_PM_NO_ACTION;
                    break;
                }
            }
        }
    }
}