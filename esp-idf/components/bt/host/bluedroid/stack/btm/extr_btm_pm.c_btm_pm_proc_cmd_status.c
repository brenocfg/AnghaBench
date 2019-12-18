#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_PM_STATUS ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ tBTM_PM_MCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_8__ {size_t pm_pend_link; size_t pm_pend_id; TYPE_2__* acl_db; TYPE_1__* pm_reg_db; TYPE_3__* pm_mode_db; } ;
struct TYPE_6__ {int /*<<< orphan*/  remote_addr; } ;
struct TYPE_5__ {int mask; int /*<<< orphan*/  (* cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BTM_PM_REG_NOTIF ; 
 size_t BTM_PM_SET_ONLY_ID ; 
 int /*<<< orphan*/  BTM_PM_STS_ERROR ; 
 int /*<<< orphan*/  BTM_PM_STS_PENDING ; 
 int /*<<< orphan*/  BTM_PM_ST_PENDING ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  HCI_SUCCESS ; 
 size_t MAX_L2CAP_LINKS ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  btm_pm_check_stored () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_pm_proc_cmd_status(UINT8 status)
{
    tBTM_PM_MCB     *p_cb;
    tBTM_PM_STATUS  pm_status;

    if (btm_cb.pm_pend_link >= MAX_L2CAP_LINKS) {
        return;
    }

    p_cb = &btm_cb.pm_mode_db[btm_cb.pm_pend_link];

    if (status == HCI_SUCCESS) {
        p_cb->state = BTM_PM_ST_PENDING;
        pm_status = BTM_PM_STS_PENDING;
#if BTM_PM_DEBUG == TRUE
        BTM_TRACE_DEBUG( "btm_pm_proc_cmd_status new state:0x%x", p_cb->state);
#endif // BTM_PM_DEBUG
    } else { /* the command was not successfull. Stay in the same state */
        pm_status = BTM_PM_STS_ERROR;
    }

    /* notify the caller is appropriate */
    if ( (btm_cb.pm_pend_id != BTM_PM_SET_ONLY_ID) &&
            (btm_cb.pm_reg_db[btm_cb.pm_pend_id].mask & BTM_PM_REG_NOTIF) ) {
        (*btm_cb.pm_reg_db[btm_cb.pm_pend_id].cback)(btm_cb.acl_db[btm_cb.pm_pend_link].remote_addr, pm_status, 0, status);
    }

    /* no pending cmd now */
#if BTM_PM_DEBUG == TRUE
    BTM_TRACE_DEBUG( "btm_pm_proc_cmd_status state:0x%x, pm_pend_link: %d(new: %d)",
                     p_cb->state, btm_cb.pm_pend_link, MAX_L2CAP_LINKS);
#endif  // BTM_PM_DEBUG
    btm_cb.pm_pend_link = MAX_L2CAP_LINKS;

    btm_pm_check_stored();
}