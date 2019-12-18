#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p_last_ccb; TYPE_3__* p_first_ccb; } ;
typedef  TYPE_2__ tL2C_CCB_Q ;
struct TYPE_8__ {scalar_t__ ccb_priority; TYPE_5__* p_lcb; struct TYPE_8__* p_prev_ccb; struct TYPE_8__* p_next_ccb; int /*<<< orphan*/  local_cid; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_3__ tL2C_CCB ;
struct TYPE_9__ {TYPE_1__* rr_serv; TYPE_2__ ccb_queue; } ;
struct TYPE_6__ {scalar_t__ num_ccb; int /*<<< orphan*/  quota; TYPE_3__* p_serve_ccb; TYPE_3__* p_first_ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_GET_PRIORITY_QUOTA (size_t) ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

void l2cu_enqueue_ccb (tL2C_CCB *p_ccb)
{
    tL2C_CCB        *p_ccb1;
    tL2C_CCB_Q      *p_q = NULL;

    /* Find out which queue the channel is on
    */
    if (p_ccb->p_lcb != NULL) {
        p_q = &p_ccb->p_lcb->ccb_queue;
    }

    if ( (!p_ccb->in_use) || (p_q == NULL) ) {
        L2CAP_TRACE_ERROR ("l2cu_enqueue_ccb  CID: 0x%04x ERROR in_use: %u  p_lcb: %p",
                           p_ccb->local_cid, p_ccb->in_use, p_ccb->p_lcb);
        return;
    }

    L2CAP_TRACE_DEBUG ("l2cu_enqueue_ccb CID: 0x%04x  priority: %d",
                       p_ccb->local_cid, p_ccb->ccb_priority);

    /* If the queue is empty, we go at the front */
    if (!p_q->p_first_ccb) {
        p_q->p_first_ccb  = p_q->p_last_ccb   = p_ccb;
        p_ccb->p_next_ccb = p_ccb->p_prev_ccb = NULL;
    } else {
        p_ccb1 = p_q->p_first_ccb;

        while (p_ccb1 != NULL) {
            /* Insert new ccb at the end of the same priority. Lower number, higher priority */
            if (p_ccb->ccb_priority < p_ccb1->ccb_priority) {
                /* Are we at the head of the queue ? */
                if (p_ccb1 == p_q->p_first_ccb) {
                    p_q->p_first_ccb = p_ccb;
                } else {
                    p_ccb1->p_prev_ccb->p_next_ccb  = p_ccb;
                }

                p_ccb->p_next_ccb  = p_ccb1;
                p_ccb->p_prev_ccb  = p_ccb1->p_prev_ccb;
                p_ccb1->p_prev_ccb = p_ccb;
                break;
            }

            p_ccb1 = p_ccb1->p_next_ccb;
        }

        /* If we are lower then anyone in the list, we go at the end */
        if (!p_ccb1) {
            /* add new ccb at the end of the list */
            p_q->p_last_ccb->p_next_ccb = p_ccb;

            p_ccb->p_next_ccb   = NULL;
            p_ccb->p_prev_ccb   = p_q->p_last_ccb;
            p_q->p_last_ccb = p_ccb;
        }
    }

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
    /* Adding CCB into round robin service table of its LCB */
    if (p_ccb->p_lcb != NULL) {
        /* if this is the first channel in this priority group */
        if (p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb == 0 ) {
            /* Set the first channel to this CCB */
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = p_ccb;
            /* Set the next serving channel in this group to this CCB */
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb = p_ccb;
            /* Initialize quota of this priority group based on its priority */
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].quota = L2CAP_GET_PRIORITY_QUOTA(p_ccb->ccb_priority);
        }
        /* increase number of channels in this group */
        p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb++;
    }
#endif

}