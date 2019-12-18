#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t local_cid; int buff_quota; TYPE_6__* p_lcb; TYPE_4__* p_rcb; int /*<<< orphan*/  xmit_hold_q; void* cong_sent; } ;
typedef  TYPE_7__ tL2C_CCB ;
typedef  size_t UINT8 ;
struct TYPE_17__ {TYPE_5__* fixed_reg; void* is_cong_cback_context; } ;
struct TYPE_15__ {int /*<<< orphan*/  remote_bd_addr; TYPE_7__** p_fixed_ccbs; int /*<<< orphan*/  ucd_out_sec_pending_q; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* pL2CA_FixedCong_Cb ) (int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* pL2CA_UCD_Congestion_Status_Cb ) (int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_12__ {TYPE_2__ cb_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* pL2CA_CongestionStatus_Cb ) (size_t,void*) ;} ;
struct TYPE_13__ {TYPE_3__ ucd; TYPE_1__ api; } ;

/* Variables and functions */
 void* FALSE ; 
 size_t L2CAP_CONNECTIONLESS_CID ; 
 size_t L2CAP_NUM_FIXED_CHNLS ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,size_t,size_t,int) ; 
 void* TRUE ; 
 size_t fixed_queue_length (int /*<<< orphan*/ ) ; 
 TYPE_9__ l2cb ; 
 int /*<<< orphan*/  stub1 (size_t,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub4 (size_t,void*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,void*) ; 

void l2cu_check_channel_congestion (tL2C_CCB *p_ccb)
{
    size_t q_count = fixed_queue_length(p_ccb->xmit_hold_q);

#if (L2CAP_UCD_INCLUDED == TRUE)
    if ( p_ccb->local_cid == L2CAP_CONNECTIONLESS_CID ) {
        q_count += fixed_queue_length(p_ccb->p_lcb->ucd_out_sec_pending_q);
    }
#endif
    /* If the CCB queue limit is subject to a quota, check for congestion */
    /* if this channel has outgoing traffic */
    if (p_ccb->buff_quota != 0) {
        /* If this channel was congested */
        if ( p_ccb->cong_sent ) {
            /* If the channel is not congested now, tell the app */
            if (q_count <= (p_ccb->buff_quota / 2)) {
                p_ccb->cong_sent = FALSE;
                if (p_ccb->p_rcb && p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb) {
                    L2CAP_TRACE_DEBUG ("L2CAP - Calling CongestionStatus_Cb (FALSE), CID: 0x%04x  xmit_hold_q.count: %u  buff_quota: %u",
                                       p_ccb->local_cid, q_count, p_ccb->buff_quota);

                    /* Prevent recursive calling */
                    l2cb.is_cong_cback_context = TRUE;
                    (*p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb)(p_ccb->local_cid, FALSE);
                    l2cb.is_cong_cback_context = FALSE;
                }
#if (L2CAP_UCD_INCLUDED == TRUE)
                else if ( p_ccb->p_rcb && p_ccb->local_cid == L2CAP_CONNECTIONLESS_CID ) {
                    if ( p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb ) {
                        L2CAP_TRACE_DEBUG ("L2CAP - Calling UCD CongestionStatus_Cb (FALSE), SecPendingQ:%u,XmitQ:%u,Quota:%u",
                                           fixed_queue_length(p_ccb->p_lcb->ucd_out_sec_pending_q),
                                           fixed_queue_length(p_ccb->xmit_hold_q),
                                           p_ccb->buff_quota);
                        p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb( p_ccb->p_lcb->remote_bd_addr, FALSE );
                    }
                }
#endif
#if (L2CAP_NUM_FIXED_CHNLS > 0)
                else {
                    UINT8 xx;
                    for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx ++) {
                        if (p_ccb->p_lcb->p_fixed_ccbs[xx] == p_ccb) {
                            if (l2cb.fixed_reg[xx].pL2CA_FixedCong_Cb != NULL) {
                                (* l2cb.fixed_reg[xx].pL2CA_FixedCong_Cb)(p_ccb->p_lcb->remote_bd_addr, FALSE);
                            }
                            break;
                        }
                    }
                }
#endif
            }
        } else {
            /* If this channel was not congested but it is congested now, tell the app */
            if (q_count > p_ccb->buff_quota) {
                p_ccb->cong_sent = TRUE;
                if (p_ccb->p_rcb && p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb) {
                    L2CAP_TRACE_DEBUG ("L2CAP - Calling CongestionStatus_Cb (TRUE),CID:0x%04x,XmitQ:%u,Quota:%u",
                                       p_ccb->local_cid, q_count, p_ccb->buff_quota);

                    (*p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb)(p_ccb->local_cid, TRUE);
                }
#if (L2CAP_UCD_INCLUDED == TRUE)
                else if ( p_ccb->p_rcb && p_ccb->local_cid == L2CAP_CONNECTIONLESS_CID ) {
                    if ( p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb ) {
                        L2CAP_TRACE_DEBUG ("L2CAP - Calling UCD CongestionStatus_Cb (TRUE), SecPendingQ:%u,XmitQ:%u,Quota:%u",
                                          fixed_queue_length(p_ccb->p_lcb->ucd_out_sec_pending_q),
                                          fixed_queue_length(p_ccb->xmit_hold_q),
                                          p_ccb->buff_quota);
                        p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb( p_ccb->p_lcb->remote_bd_addr, TRUE );
                    }
                }
#endif
#if (L2CAP_NUM_FIXED_CHNLS > 0)
                else {
                    UINT8 xx;
                    for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx ++) {
                        if (p_ccb->p_lcb->p_fixed_ccbs[xx] == p_ccb) {
                            if (l2cb.fixed_reg[xx].pL2CA_FixedCong_Cb != NULL) {
                                (* l2cb.fixed_reg[xx].pL2CA_FixedCong_Cb)(p_ccb->p_lcb->remote_bd_addr, TRUE);
                            }
                            break;
                        }
                    }
                }
#endif
            }
        }
    }
}