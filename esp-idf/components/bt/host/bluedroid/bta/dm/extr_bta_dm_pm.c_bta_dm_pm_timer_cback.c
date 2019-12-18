#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  event; } ;
struct TYPE_8__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  pm_request; TYPE_1__ hdr; } ;
typedef  TYPE_3__ tBTA_DM_PM_TIMER ;
typedef  size_t UINT8 ;
struct TYPE_9__ {TYPE_2__* pm_timer; } ;
struct TYPE_7__ {size_t in_use; scalar_t__ active; int /*<<< orphan*/  peer_bdaddr; int /*<<< orphan*/ * pm_action; int /*<<< orphan*/ * srvc_id; int /*<<< orphan*/ * timer; } ;
typedef  int /*<<< orphan*/  TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,size_t,size_t) ; 
 size_t BTA_DM_NUM_PM_TIMER ; 
 size_t BTA_DM_PM_MODE_TIMER_MAX ; 
 int /*<<< orphan*/  BTA_DM_PM_TIMER_EVT ; 
 int /*<<< orphan*/  BTA_ID_MAX ; 
 size_t FALSE ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_3__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_dm_pm_timer_cback(void *p_tle)
{
    UINT8 i, j;

    for (i = 0; i < BTA_DM_NUM_PM_TIMER; i++) {
        APPL_TRACE_DEBUG("dm_pm_timer[%d] in use? %d", i, bta_dm_cb.pm_timer[i].in_use);
        if (bta_dm_cb.pm_timer[i].in_use) {
            for (j = 0; j < BTA_DM_PM_MODE_TIMER_MAX; j++) {
                if (&bta_dm_cb.pm_timer[i].timer[j] == (TIMER_LIST_ENT *) p_tle) {
                    bta_dm_cb.pm_timer[i].active --;
                    bta_dm_cb.pm_timer[i].srvc_id[j] = BTA_ID_MAX;
                    APPL_TRACE_DEBUG("dm_pm_timer[%d] expires, timer_idx=%d", i, j);
                    break;
                }
            }
            if (bta_dm_cb.pm_timer[i].active == 0) {
                bta_dm_cb.pm_timer[i].in_use = FALSE;
            }
            if (j < BTA_DM_PM_MODE_TIMER_MAX) {
                break;
            }
        }
    }

    /* no more timers */
    if (i == BTA_DM_NUM_PM_TIMER) {
        return;
    }

    tBTA_DM_PM_TIMER *p_buf = (tBTA_DM_PM_TIMER *) osi_malloc(sizeof(tBTA_DM_PM_TIMER));
    if (p_buf != NULL) {
        p_buf->hdr.event = BTA_DM_PM_TIMER_EVT;
        p_buf->pm_request = bta_dm_cb.pm_timer[i].pm_action[j];
        bdcpy(p_buf->bd_addr, bta_dm_cb.pm_timer[i].peer_bdaddr);
        bta_sys_sendmsg(p_buf);
    }
}