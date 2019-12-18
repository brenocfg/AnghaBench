#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int mode; } ;
typedef  TYPE_2__ tBTM_PM_PWR_MD ;
typedef  scalar_t__ tBTM_PM_MODE ;
struct TYPE_14__ {TYPE_2__* req_mode; } ;
typedef  TYPE_3__ tBTM_PM_MCB ;
typedef  scalar_t__ UINT8 ;
struct TYPE_12__ {int mask; } ;
struct TYPE_11__ {TYPE_1__* pm_reg_db; } ;

/* Variables and functions */
 int BTM_MAX_PM_RECORDS ; 
 scalar_t__ BTM_PM_MD_ACTIVE ; 
 int BTM_PM_MD_FORCE ; 
 int BTM_PM_REG_SET ; 
 scalar_t__ BTM_PM_SET_ONLY_ID ; 
 TYPE_10__ btm_cb ; 
 int /*<<< orphan*/ * btm_pm_compare_modes (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static tBTM_PM_MODE btm_pm_get_set_mode(UINT8 pm_id, tBTM_PM_MCB *p_cb, tBTM_PM_PWR_MD *p_mode, tBTM_PM_PWR_MD *p_res)
{
    int   xx, loop_max;
    tBTM_PM_PWR_MD *p_md = NULL;

    if (p_mode != NULL && p_mode->mode & BTM_PM_MD_FORCE) {
        *p_res = *p_mode;
        p_res->mode &= ~BTM_PM_MD_FORCE;
        return p_res->mode;
    }

    if (!p_mode) {
        loop_max = BTM_MAX_PM_RECORDS + 1;
    } else {
        loop_max = BTM_MAX_PM_RECORDS;
    }

    for ( xx = 0; xx < loop_max; xx++) {
        /* g through all the registered "set" parties */
        if (btm_cb.pm_reg_db[xx].mask & BTM_PM_REG_SET) {
            if (p_cb->req_mode[xx].mode == BTM_PM_MD_ACTIVE) {
                /* if at least one registered (SET) party says ACTIVE, stay active */
                return BTM_PM_MD_ACTIVE;
            } else {
                /* if registered parties give conflicting information, stay active */
                if ( (btm_pm_compare_modes(p_md, &p_cb->req_mode[xx], p_res)) == NULL) {
                    return BTM_PM_MD_ACTIVE;
                }
                p_md = p_res;
            }
        }
    }

    /* if the resulting mode is NULL(nobody registers SET), use the requested mode */
    if (p_md == NULL) {
        if (p_mode) {
            *p_res = *((tBTM_PM_PWR_MD *)p_mode);
        } else { /* p_mode is NULL when btm_pm_snd_md_req is called from btm_pm_proc_mode_change */
            return BTM_PM_MD_ACTIVE;
        }
    } else {
        /* if the command is from unregistered party,
           compare the resulting mode from registered party*/
        if ( (pm_id == BTM_PM_SET_ONLY_ID) &&
                ((btm_pm_compare_modes(p_mode, p_md, p_res)) == NULL) ) {
            return BTM_PM_MD_ACTIVE;
        }
    }

    return p_res->mode;
}