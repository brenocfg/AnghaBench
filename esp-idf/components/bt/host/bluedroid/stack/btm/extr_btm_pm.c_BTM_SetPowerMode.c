#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_8__ {int mode; scalar_t__ max; scalar_t__ min; } ;
typedef  TYPE_2__ tBTM_PM_PWR_MD ;
typedef  int tBTM_PM_MODE ;
struct TYPE_9__ {int state; scalar_t__ interval; int /*<<< orphan*/  chg_ind; TYPE_2__* req_mode; } ;
typedef  TYPE_3__ tBTM_PM_MCB ;
typedef  size_t UINT8 ;
struct TYPE_10__ {int pm_pend_link; TYPE_1__* pm_reg_db; TYPE_3__* pm_mode_db; } ;
struct TYPE_7__ {int mask; } ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STORED ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 size_t BTM_MAX_PM_RECORDS ; 
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int BTM_PM_MD_ACTIVE ; 
 int BTM_PM_MD_FORCE ; 
 int BTM_PM_MD_HOLD ; 
 int BTM_PM_REG_SET ; 
 size_t BTM_PM_SET_ONLY_ID ; 
 int BTM_PM_STORED_MASK ; 
 int BTM_PM_STS_HOLD ; 
 int BTM_PM_STS_PENDING ; 
 size_t* BTM_ReadLocalFeatures () ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,size_t,int,int) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ btm_cb ; 
 int btm_pm_find_acl_ind (int*) ; 
 size_t* btm_pm_mode_msk ; 
 size_t* btm_pm_mode_off ; 
 int /*<<< orphan*/  btm_pm_snd_md_req (size_t,int,TYPE_2__*) ; 

tBTM_STATUS BTM_SetPowerMode (UINT8 pm_id, BD_ADDR remote_bda, tBTM_PM_PWR_MD *p_mode)
{
    UINT8               *p_features;
    int               ind, acl_ind;
    tBTM_PM_MCB *p_cb = NULL;   /* per ACL link */
    tBTM_PM_MODE        mode;
    int                 temp_pm_id;


    if (pm_id >= BTM_MAX_PM_RECORDS) {
        pm_id = BTM_PM_SET_ONLY_ID;
    }

    if (p_mode == NULL) {
        return BTM_ILLEGAL_VALUE;
    }

    BTM_TRACE_API( "BTM_SetPowerMode: pm_id %d BDA: %08x mode:0x%x", pm_id,
                   (remote_bda[2] << 24) + (remote_bda[3] << 16) + (remote_bda[4] << 8) + remote_bda[5], p_mode->mode);

    /* take out the force bit */
    mode = p_mode->mode & ~BTM_PM_MD_FORCE;

    acl_ind = btm_pm_find_acl_ind(remote_bda);
    if (acl_ind == MAX_L2CAP_LINKS) {
        return (BTM_UNKNOWN_ADDR);
    }

    p_cb = &(btm_cb.pm_mode_db[acl_ind]);

    if (mode != BTM_PM_MD_ACTIVE) {
        /* check if the requested mode is supported */
        ind = mode - BTM_PM_MD_HOLD; /* make it base 0 */
        p_features = BTM_ReadLocalFeatures();
        if ( !(p_features[ btm_pm_mode_off[ind] ] & btm_pm_mode_msk[ind] ) ) {
            return BTM_MODE_UNSUPPORTED;
        }
    }

    if (mode == p_cb->state) { /* the requested mode is current mode */
        /* already in the requested mode and the current interval has less latency than the max */
        if ( (mode == BTM_PM_MD_ACTIVE) ||
                ((p_mode->mode & BTM_PM_MD_FORCE) && (p_mode->max >= p_cb->interval) && (p_mode->min <= p_cb->interval)) ||
                ((p_mode->mode & BTM_PM_MD_FORCE) == 0 && (p_mode->max >= p_cb->interval)) ) {
            BTM_TRACE_DEBUG( "BTM_SetPowerMode: mode:0x%x interval %d max:%d, min:%d", p_mode->mode, p_cb->interval, p_mode->max, p_mode->min);
            return BTM_SUCCESS;
        }
    }

    temp_pm_id = pm_id;
    if (pm_id == BTM_PM_SET_ONLY_ID) {
        temp_pm_id = BTM_MAX_PM_RECORDS;
    }

    /* update mode database */
    if ( ((pm_id != BTM_PM_SET_ONLY_ID) &&
            (btm_cb.pm_reg_db[pm_id].mask & BTM_PM_REG_SET))
            || ((pm_id == BTM_PM_SET_ONLY_ID) && (btm_cb.pm_pend_link != MAX_L2CAP_LINKS)) ) {
#if BTM_PM_DEBUG == TRUE
        BTM_TRACE_DEBUG( "BTM_SetPowerMode: Saving cmd acl_ind %d temp_pm_id %d", acl_ind, temp_pm_id);
#endif  // BTM_PM_DEBUG
        /* Make sure mask is set to BTM_PM_REG_SET */
        btm_cb.pm_reg_db[temp_pm_id].mask |= BTM_PM_REG_SET;
        *(&p_cb->req_mode[temp_pm_id]) = *((tBTM_PM_PWR_MD *)p_mode);
        p_cb->chg_ind = TRUE;
    }

#if BTM_PM_DEBUG == TRUE
    BTM_TRACE_DEBUG( "btm_pm state:0x%x, pm_pend_link: %d", p_cb->state, btm_cb.pm_pend_link);
#endif  // BTM_PM_DEBUG
    /* if mode == hold or pending, return */
    if ( (p_cb->state == BTM_PM_STS_HOLD) ||
            (p_cb->state ==  BTM_PM_STS_PENDING) ||
            (btm_cb.pm_pend_link != MAX_L2CAP_LINKS) ) { /* command pending */
        if (acl_ind != btm_cb.pm_pend_link) {
            /* set the stored mask */
            p_cb->state |= BTM_PM_STORED_MASK;
            BTM_TRACE_DEBUG( "btm_pm state stored:%d", acl_ind);
        }
        return BTM_CMD_STORED;
    }



    return btm_pm_snd_md_req(pm_id, acl_ind, p_mode);
}