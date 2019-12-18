#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ num_tries; scalar_t__ local_busy; int /*<<< orphan*/  rej_sent; int /*<<< orphan*/  srej_sent; int /*<<< orphan*/  retrans_touts; int /*<<< orphan*/  waiting_for_ack_q; int /*<<< orphan*/  wait_ack; } ;
struct TYPE_8__ {scalar_t__ max_transmit; } ;
struct TYPE_9__ {TYPE_1__ fcr; } ;
struct TYPE_11__ {TYPE_3__ fcrb; TYPE_2__ peer_cfg; int /*<<< orphan*/  local_cid; } ;
typedef  TYPE_4__ tL2C_CCB ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_FCR_P_BIT ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_RNR ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_RR ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_fcr_send_S_frame (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_disconnect_chnl (TYPE_4__*) ; 

void l2c_fcr_proc_tout (tL2C_CCB *p_ccb)
{
    assert(p_ccb != NULL);
    L2CAP_TRACE_DEBUG ("l2c_fcr_proc_tout:  CID: 0x%04x  num_tries: %u (max: %u)  wait_ack: %u  ack_q_count: %u",
                       p_ccb->local_cid, p_ccb->fcrb.num_tries,
                       p_ccb->peer_cfg.fcr.max_transmit,
                       p_ccb->fcrb.wait_ack,
                       fixed_queue_length(p_ccb->fcrb.waiting_for_ack_q));

#if (L2CAP_ERTM_STATS == TRUE)
    p_ccb->fcrb.retrans_touts++;
#endif

    if ( (p_ccb->peer_cfg.fcr.max_transmit != 0) && (++p_ccb->fcrb.num_tries > p_ccb->peer_cfg.fcr.max_transmit) ) {
        l2cu_disconnect_chnl (p_ccb);
    } else {
        if (!p_ccb->fcrb.srej_sent && !p_ccb->fcrb.rej_sent) {
            if (p_ccb->fcrb.local_busy) {
                l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RNR, L2CAP_FCR_P_BIT);
            } else {
                l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RR, L2CAP_FCR_P_BIT);
            }
        }
    }
}