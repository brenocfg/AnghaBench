#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ next_seq_expected; scalar_t__ last_ack_sent; scalar_t__ local_busy; int /*<<< orphan*/  xmit_ack_touts; int /*<<< orphan*/  wait_ack; } ;
struct TYPE_6__ {scalar_t__ chnl_state; TYPE_1__ fcrb; int /*<<< orphan*/  local_cid; } ;
typedef  TYPE_2__ tL2C_CCB ;

/* Variables and functions */
 scalar_t__ CST_OPEN ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_RNR ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_RR ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_fcr_send_S_frame (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2c_fcr_proc_ack_tout (tL2C_CCB *p_ccb)
{
    assert(p_ccb != NULL);
    L2CAP_TRACE_DEBUG ("l2c_fcr_proc_ack_tout:  CID: 0x%04x State: %u  Wack:%u  Rq:%d  Acked:%d", p_ccb->local_cid,
                       p_ccb->chnl_state, p_ccb->fcrb.wait_ack, p_ccb->fcrb.next_seq_expected, p_ccb->fcrb.last_ack_sent);

    if ( (p_ccb->chnl_state == CST_OPEN) && (!p_ccb->fcrb.wait_ack)
            && (p_ccb->fcrb.last_ack_sent != p_ccb->fcrb.next_seq_expected) ) {
#if (L2CAP_ERTM_STATS == TRUE)
        p_ccb->fcrb.xmit_ack_touts++;
#endif
        if (p_ccb->fcrb.local_busy) {
            l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RNR, 0);
        } else {
            l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RR, 0);
        }
    }
}