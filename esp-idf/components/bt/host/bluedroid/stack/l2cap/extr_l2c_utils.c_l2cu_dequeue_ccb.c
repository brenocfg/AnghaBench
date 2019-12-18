#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* p_last_ccb; TYPE_3__* p_first_ccb; } ;
typedef  TYPE_2__ tL2C_CCB_Q ;
struct TYPE_10__ {size_t ccb_priority; struct TYPE_10__* p_prev_ccb; struct TYPE_10__* p_next_ccb; TYPE_5__* p_lcb; int /*<<< orphan*/  in_use; int /*<<< orphan*/  local_cid; } ;
typedef  TYPE_3__ tL2C_CCB ;
struct TYPE_11__ {TYPE_1__* rr_serv; TYPE_2__ ccb_queue; } ;
struct TYPE_8__ {scalar_t__ num_ccb; TYPE_3__* p_first_ccb; TYPE_3__* p_serve_ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,TYPE_2__*,TYPE_3__*) ; 

void l2cu_dequeue_ccb (tL2C_CCB *p_ccb)
{
    tL2C_CCB_Q      *p_q = NULL;

    L2CAP_TRACE_DEBUG ("l2cu_dequeue_ccb  CID: 0x%04x", p_ccb->local_cid);

    /* Find out which queue the channel is on
    */
    if (p_ccb->p_lcb != NULL) {
        p_q = &p_ccb->p_lcb->ccb_queue;
    }

    if ( (!p_ccb->in_use) || (p_q == NULL) || (p_q->p_first_ccb == NULL) ) {
        L2CAP_TRACE_ERROR ("l2cu_dequeue_ccb  CID: 0x%04x ERROR in_use: %u  p_lcb: %p  p_q: %p  p_q->p_first_ccb: %p",
                           p_ccb->local_cid, p_ccb->in_use, p_ccb->p_lcb, p_q, p_q ? p_q->p_first_ccb : 0);
        return;
    }

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
    /* Removing CCB from round robin service table of its LCB */
    if (p_ccb->p_lcb != NULL) {
        /* decrease number of channels in this priority group */
        p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb--;

        /* if it was the last channel in the priority group */
        if (p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb == 0 ) {
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = NULL;
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb = NULL;
        } else {
            /* if it is the first channel of this group */
            if ( p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb == p_ccb ) {
                p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = p_ccb->p_next_ccb;
            }
            /* if it is the next serving channel of this group */
            if ( p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb == p_ccb ) {
                /* simply, start serving from the first channel */
                p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb
                    = p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb;
            }
        }
    }
#endif

    if (p_ccb == p_q->p_first_ccb) {
        /* We are removing the first in a queue */
        p_q->p_first_ccb = p_ccb->p_next_ccb;

        if (p_q->p_first_ccb) {
            p_q->p_first_ccb->p_prev_ccb = NULL;
        } else {
            p_q->p_last_ccb = NULL;
        }
    } else if (p_ccb == p_q->p_last_ccb) {
        /* We are removing the last in a queue */
        p_q->p_last_ccb = p_ccb->p_prev_ccb;
        p_q->p_last_ccb->p_next_ccb = NULL;
    } else {
        /* In the middle of a chain. */
        p_ccb->p_prev_ccb->p_next_ccb = p_ccb->p_next_ccb;
        p_ccb->p_next_ccb->p_prev_ccb = p_ccb->p_prev_ccb;
    }

    p_ccb->p_next_ccb = p_ccb->p_prev_ccb = NULL;
}