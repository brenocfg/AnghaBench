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
struct TYPE_5__ {TYPE_3__* p_first_ccb; TYPE_3__* p_last_ccb; } ;
struct TYPE_6__ {scalar_t__ link_state; TYPE_1__ ccb_queue; scalar_t__ in_use; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_7__ {scalar_t__ chnl_state; scalar_t__ in_use; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {TYPE_2__* lcb_pool; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ CST_W4_L2CAP_DISCONNECT_RSP ; 
 scalar_t__ CST_W4_L2CA_DISCONNECT_RSP ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LST_DISCONNECTING ; 
 scalar_t__ MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ l2cb ; 

BOOLEAN l2cu_lcb_disconnecting (void)
{
    tL2C_LCB    *p_lcb;
    tL2C_CCB    *p_ccb;
    UINT16      i;
    BOOLEAN     status = FALSE;

    p_lcb = &l2cb.lcb_pool[0];

    for (i = 0; i < MAX_L2CAP_LINKS; i++, p_lcb++) {
        if (p_lcb->in_use) {
            /* no ccbs on lcb, or lcb is in disconnecting state */
            if ((!p_lcb->ccb_queue.p_first_ccb) || (p_lcb->link_state == LST_DISCONNECTING)) {
                status = TRUE;
                break;
            }
            /* only one ccb left on lcb */
            else if (p_lcb->ccb_queue.p_first_ccb == p_lcb->ccb_queue.p_last_ccb) {
                p_ccb = p_lcb->ccb_queue.p_first_ccb;

                if ((p_ccb->in_use) &&
                        ((p_ccb->chnl_state == CST_W4_L2CAP_DISCONNECT_RSP) ||
                         (p_ccb->chnl_state == CST_W4_L2CA_DISCONNECT_RSP))) {
                    status = TRUE;
                    break;
                }
            }
        }
    }
    return status;
}