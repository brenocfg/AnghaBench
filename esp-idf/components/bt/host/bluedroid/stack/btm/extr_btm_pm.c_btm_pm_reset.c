#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* tBTM_PM_STATUS_CBACK ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_6__ {size_t pm_pend_id; size_t pm_pend_link; TYPE_1__* acl_db; TYPE_2__* pm_reg_db; } ;
struct TYPE_5__ {int mask; int /*<<< orphan*/  (* cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  remote_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_DEV_RESET ; 
 int BTM_MAX_PM_RECORDS ; 
 int BTM_PM_REC_NOT_USED ; 
 int BTM_PM_REG_NOTIF ; 
 size_t BTM_PM_SET_ONLY_ID ; 
 int /*<<< orphan*/  BTM_PM_STS_ERROR ; 
 size_t MAX_L2CAP_LINKS ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_pm_reset(void)
{
    int xx;
    tBTM_PM_STATUS_CBACK *cb = NULL;

    /* clear the pending request for application */
    if ( (btm_cb.pm_pend_id != BTM_PM_SET_ONLY_ID) &&
            (btm_cb.pm_reg_db[btm_cb.pm_pend_id].mask & BTM_PM_REG_NOTIF) ) {
        cb = btm_cb.pm_reg_db[btm_cb.pm_pend_id].cback;
    }


    /* clear the register record */
    for (xx = 0; xx < BTM_MAX_PM_RECORDS; xx++) {
        btm_cb.pm_reg_db[xx].mask = BTM_PM_REC_NOT_USED;
    }

    if (cb != NULL && btm_cb.pm_pend_link < MAX_L2CAP_LINKS) {
        (*cb)(btm_cb.acl_db[btm_cb.pm_pend_link].remote_addr, BTM_PM_STS_ERROR, BTM_DEV_RESET, 0);
    }

    /* no command pending */
    btm_cb.pm_pend_link = MAX_L2CAP_LINKS;
}