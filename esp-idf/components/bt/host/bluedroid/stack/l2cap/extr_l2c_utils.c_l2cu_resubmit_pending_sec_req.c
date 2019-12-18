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
struct TYPE_7__ {TYPE_3__* p_first_ccb; } ;
struct TYPE_8__ {TYPE_1__ ccb_queue; scalar_t__ in_use; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_9__ {struct TYPE_9__* p_next_ccb; } ;
typedef  TYPE_3__ tL2C_CCB ;
struct TYPE_10__ {TYPE_2__* lcb_pool; } ;
typedef  scalar_t__ BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  L2CEVT_SEC_RE_SEND_CMD ; 
 int MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ l2cb ; 
 TYPE_2__* l2cu_find_lcb_by_bd_addr (scalar_t__,int /*<<< orphan*/ ) ; 

void l2cu_resubmit_pending_sec_req (BD_ADDR p_bda)
{
    tL2C_LCB        *p_lcb;
    tL2C_CCB        *p_ccb;
    tL2C_CCB        *p_next_ccb;
    int             xx;
    L2CAP_TRACE_DEBUG ("l2cu_resubmit_pending_sec_req  p_bda: %p", p_bda);

    /* If we are called with a BDA, only resubmit for that BDA */
    if (p_bda) {
        p_lcb = l2cu_find_lcb_by_bd_addr (p_bda, BT_TRANSPORT_BR_EDR);
        /* If we don't have one, this is an error */
        if (p_lcb) {
            /* For all channels, send the event through their FSMs */
            for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_next_ccb) {
                p_next_ccb = p_ccb->p_next_ccb;
                l2c_csm_execute (p_ccb, L2CEVT_SEC_RE_SEND_CMD, NULL);
            }
        } else {
            L2CAP_TRACE_WARNING ("l2cu_resubmit_pending_sec_req - unknown BD_ADDR");
        }
    } else {
        /* No BDA pasesed in, so check all links */
        for (xx = 0, p_lcb = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb++) {
            if (p_lcb->in_use) {
                /* For all channels, send the event through their FSMs */
                for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_next_ccb) {
                    p_next_ccb = p_ccb->p_next_ccb;
                    l2c_csm_execute (p_ccb, L2CEVT_SEC_RE_SEND_CMD, NULL);
                }
            }
        }
    }
}