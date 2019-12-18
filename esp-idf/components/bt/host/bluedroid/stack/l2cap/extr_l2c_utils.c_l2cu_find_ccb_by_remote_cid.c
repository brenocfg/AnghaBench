#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* p_first_ccb; } ;
struct TYPE_7__ {TYPE_1__ ccb_queue; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_8__ {scalar_t__ remote_cid; scalar_t__ in_use; struct TYPE_8__* p_next_ccb; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */

tL2C_CCB *l2cu_find_ccb_by_remote_cid (tL2C_LCB *p_lcb, UINT16 remote_cid)
{
    tL2C_CCB    *p_ccb;

    /* If LCB is NULL, look through all active links */
    if (!p_lcb) {
        return NULL;
    } else {
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
            if ((p_ccb->in_use) && (p_ccb->remote_cid == remote_cid)) {
                return (p_ccb);
            }
    }

    /* If here, no match found */
    return (NULL);
}