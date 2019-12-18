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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_PM_STATUS_CBACK ;
typedef  int UINT8 ;
struct TYPE_4__ {TYPE_1__* pm_reg_db; } ;
struct TYPE_3__ {int mask; int /*<<< orphan*/ * cback; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int BTM_MAX_PM_RECORDS ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int BTM_PM_DEREG ; 
 int BTM_PM_REC_NOT_USED ; 
 int BTM_PM_REG_NOTIF ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 TYPE_2__ btm_cb ; 

tBTM_STATUS BTM_PmRegister (UINT8 mask, UINT8 *p_pm_id, tBTM_PM_STATUS_CBACK *p_cb)
{
    int xx;

    /* de-register */
    if (mask & BTM_PM_DEREG) {
        if (*p_pm_id >= BTM_MAX_PM_RECORDS) {
            return BTM_ILLEGAL_VALUE;
        }
        btm_cb.pm_reg_db[*p_pm_id].mask = BTM_PM_REC_NOT_USED;
        return BTM_SUCCESS;
    }

    for (xx = 0; xx < BTM_MAX_PM_RECORDS; xx++) {
        /* find an unused entry */
        if (btm_cb.pm_reg_db[xx].mask == BTM_PM_REC_NOT_USED) {
            /* if register for notification, should provide callback routine */
            if (mask & BTM_PM_REG_NOTIF) {
                if (p_cb == NULL) {
                    return BTM_ILLEGAL_VALUE;
                }
                btm_cb.pm_reg_db[xx].cback = p_cb;
            }
            btm_cb.pm_reg_db[xx].mask = mask;
            *p_pm_id = xx;
            return BTM_SUCCESS;
        }
    }

    return BTM_NO_RESOURCES;
}