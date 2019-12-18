#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_8__** p_fixed_ccbs; } ;
typedef  TYPE_7__ tL2C_LCB ;
struct TYPE_22__ {scalar_t__ mode; } ;
struct TYPE_23__ {TYPE_3__ fcr; } ;
struct TYPE_20__ {int /*<<< orphan*/  retrans_q; scalar_t__ remote_busy; scalar_t__ wait_ack; } ;
struct TYPE_27__ {int /*<<< orphan*/  local_cid; TYPE_6__* p_rcb; TYPE_4__ peer_cfg; int /*<<< orphan*/  xmit_hold_q; TYPE_1__ fcrb; } ;
typedef  TYPE_8__ tL2C_CCB ;
struct TYPE_24__ {int /*<<< orphan*/  (* pL2CA_TxComplete_Cb ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_25__ {TYPE_5__ api; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* pL2CA_FixedTxComplete_Cb ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_19__ {TYPE_2__* fixed_reg; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 scalar_t__ L2CAP_FCR_BASIC_MODE ; 
 scalar_t__ L2CAP_FCR_ERTM_MODE ; 
 int L2CAP_NUM_FIXED_CHNLS ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * l2c_fcr_get_next_xmit_sdu_seg (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ l2c_fcr_is_flow_controlled (TYPE_8__*) ; 
 TYPE_16__ l2cb ; 
 int /*<<< orphan*/  l2cu_check_channel_congestion (TYPE_8__*) ; 
 TYPE_8__* l2cu_get_next_channel (TYPE_7__*) ; 
 TYPE_8__* l2cu_get_next_channel_in_rr (TYPE_7__*) ; 
 int /*<<< orphan*/  l2cu_set_acl_hci_header (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

BT_HDR *l2cu_get_next_buffer_to_send (tL2C_LCB *p_lcb)
{
    tL2C_CCB    *p_ccb;
    BT_HDR      *p_buf = NULL;

    /* Highest priority are fixed channels */
#if (L2CAP_NUM_FIXED_CHNLS > 0)
    int         xx;

    for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx++) {
        if ((p_ccb = p_lcb->p_fixed_ccbs[xx]) == NULL) {
            continue;
        }

        /* eL2CAP option in use */
        if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_BASIC_MODE) {
#if (CLASSIC_BT_INCLUDED == TRUE)
            if (p_ccb->fcrb.wait_ack || p_ccb->fcrb.remote_busy) {
                continue;
            }

            /* No more checks needed if sending from the reatransmit queue */
            if (fixed_queue_is_empty(p_ccb->fcrb.retrans_q))
            {
                if (fixed_queue_is_empty(p_ccb->xmit_hold_q)) {
                    continue;
                }
                /* If in eRTM mode, check for window closure */
                if ( (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) && (l2c_fcr_is_flow_controlled (p_ccb)) ) {
                    continue;
                }
            }
            if ((p_buf = l2c_fcr_get_next_xmit_sdu_seg(p_ccb, 0)) != NULL) {
                l2cu_check_channel_congestion (p_ccb);
                l2cu_set_acl_hci_header (p_buf, p_ccb);
                return (p_buf);
            }
#else
            continue;
#endif  ///CLASSIC_BT_INCLUDED == TRUE

        } else {
            if (!fixed_queue_is_empty(p_ccb->xmit_hold_q)) {
                p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->xmit_hold_q, 0);
                if (NULL == p_buf) {
                    L2CAP_TRACE_ERROR("l2cu_get_buffer_to_send: No data to be sent");
                    return (NULL);
                }
                /* send tx complete */
                if (l2cb.fixed_reg[xx].pL2CA_FixedTxComplete_Cb) {
                    (*l2cb.fixed_reg[xx].pL2CA_FixedTxComplete_Cb)(p_ccb->local_cid, 1);
                }

                l2cu_check_channel_congestion (p_ccb);
                l2cu_set_acl_hci_header (p_buf, p_ccb);
                return (p_buf);
            }
        }
    }
#endif
#if (CLASSIC_BT_INCLUDED == TRUE)
#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
    /* get next serving channel in round-robin */
    p_ccb  = l2cu_get_next_channel_in_rr( p_lcb );
#else
    p_ccb  = l2cu_get_next_channel( p_lcb );
#endif

    /* Return if no buffer */
    if (p_ccb == NULL) {
        return (NULL);
    }

    if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_BASIC_MODE) {

        if ((p_buf = l2c_fcr_get_next_xmit_sdu_seg(p_ccb, 0)) == NULL) {
            return (NULL);
        }

    } else {
        p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->xmit_hold_q, 0);
        if (NULL == p_buf) {
            L2CAP_TRACE_ERROR("l2cu_get_buffer_to_send() #2: No data to be sent");
            return (NULL);
        }
    }

    if ( p_ccb->p_rcb && p_ccb->p_rcb->api.pL2CA_TxComplete_Cb && (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_ERTM_MODE) ) {
        (*p_ccb->p_rcb->api.pL2CA_TxComplete_Cb)(p_ccb->local_cid, 1);
    }


    l2cu_check_channel_congestion (p_ccb);

    l2cu_set_acl_hci_header (p_buf, p_ccb);
#endif  ///CLASSIC_BT_INCLUDED == TRUE

    return (p_buf);
}