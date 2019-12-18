#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tL2C_LCB ;
struct TYPE_4__ {scalar_t__ local_cid; int /*<<< orphan*/ * p_lcb; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_CCB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {TYPE_1__* ccb_pool; } ;

/* Variables and functions */
 scalar_t__ L2CAP_BASE_APPL_CID ; 
 scalar_t__ MAX_L2CAP_CHANNELS ; 
 TYPE_3__ l2cb ; 

tL2C_CCB *l2cu_find_ccb_by_cid (tL2C_LCB *p_lcb, UINT16 local_cid)
{
    tL2C_CCB    *p_ccb = NULL;
#if (L2CAP_UCD_INCLUDED == TRUE)
    UINT8 xx;
#endif

    if (local_cid >= L2CAP_BASE_APPL_CID) {
        /* find the associated CCB by "index" */
        local_cid -= L2CAP_BASE_APPL_CID;

        if (local_cid >= MAX_L2CAP_CHANNELS) {
            return NULL;
        }

        p_ccb = l2cb.ccb_pool + local_cid;

        /* make sure the CCB is in use */
        if (!p_ccb->in_use) {
            p_ccb = NULL;
        }
        /* make sure it's for the same LCB */
        else if (p_lcb && p_lcb != p_ccb->p_lcb) {
            p_ccb = NULL;
        }
    }
#if (L2CAP_UCD_INCLUDED == TRUE)
    else {
        /* searching fixed channel */
        p_ccb = l2cb.ccb_pool;
        for ( xx = 0; xx < MAX_L2CAP_CHANNELS; xx++ ) {
            if ((p_ccb->local_cid == local_cid)
                    && (p_ccb->in_use)
                    && (p_lcb == p_ccb->p_lcb)) {
                break;
            } else {
                p_ccb++;
            }
        }
        if ( xx >= MAX_L2CAP_CHANNELS ) {
            return NULL;
        }
    }
#endif

    return (p_ccb);
}