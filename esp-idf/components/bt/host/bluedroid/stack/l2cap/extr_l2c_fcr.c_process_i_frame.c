#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  in_use; } ;
struct TYPE_25__ {int next_seq_expected; int last_ack_sent; int max_held_acks; scalar_t__ local_busy; int /*<<< orphan*/  srej_rcv_hold_q; TYPE_19__ ack_timer; void* srej_sent; void* rej_sent; void* rej_after_srej; int /*<<< orphan*/ * ertm_byte_counts; int /*<<< orphan*/ * ertm_pkt_counts; } ;
typedef  TYPE_4__ tL2C_FCRB ;
struct TYPE_23__ {int tx_win_sz; } ;
struct TYPE_24__ {TYPE_2__ fcr; } ;
struct TYPE_22__ {scalar_t__ fcr_rx_buf_size; } ;
struct TYPE_26__ {int local_cid; scalar_t__ chnl_state; TYPE_4__ fcrb; int /*<<< orphan*/  xmit_hold_q; scalar_t__ in_use; TYPE_3__ our_cfg; TYPE_1__ ertm_info; } ;
typedef  TYPE_5__ tL2C_CCB ;
typedef  int UINT8 ;
typedef  int UINT16 ;
struct TYPE_27__ {int layer_specific; scalar_t__ len; int /*<<< orphan*/  offset; } ;
typedef  TYPE_6__ BT_HDR ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_FCR_ACK ; 
 scalar_t__ CST_OPEN ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int L2CAP_FCR_ACK_TOUT ; 
 int L2CAP_FCR_F_BIT ; 
 scalar_t__ L2CAP_FCR_OVERHEAD ; 
 scalar_t__ L2CAP_FCR_RX_BUF_SIZE ; 
 int L2CAP_FCR_SEQ_MODULO ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_REJ ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_RNR ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_RR ; 
 int /*<<< orphan*/  L2CAP_FCR_SUP_SREJ ; 
 int L2CAP_FCR_TX_SEQ_BITS ; 
 int L2CAP_FCR_TX_SEQ_BITS_SHIFT ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int,int,int,void*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,int,int,int) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int,...) ; 
 int /*<<< orphan*/  L2C_FCR_RETX_ALL_PKTS ; 
 int QUICK_TIMER_TICKS_PER_SEC ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_quick_timer (TYPE_19__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btu_stop_quick_timer (TYPE_19__*) ; 
 int /*<<< orphan*/  do_sar_reassembly (TYPE_5__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 int fixed_queue_length (int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_try_peek_last (int /*<<< orphan*/ ) ; 
 TYPE_6__* l2c_fcr_clone_buf (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ l2c_fcr_is_flow_controlled (TYPE_5__*) ; 
 int /*<<< orphan*/  l2c_fcr_send_S_frame (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_disconnect_chnl (TYPE_5__*) ; 
 int /*<<< orphan*/  osi_free (TYPE_6__*) ; 
 int /*<<< orphan*/  retransmit_i_frames (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_i_frame (tL2C_CCB *p_ccb, BT_HDR *p_buf, UINT16 ctrl_word, BOOLEAN delay_ack)
{
    assert(p_ccb != NULL);
    assert(p_buf != NULL);

    tL2C_FCRB   *p_fcrb = &p_ccb->fcrb;
    UINT8       tx_seq, num_lost, num_to_ack, next_srej;

    /* If we were doing checkpoint recovery, first retransmit all unacked I-frames */
    if (ctrl_word & L2CAP_FCR_F_BIT) {
        if (!retransmit_i_frames (p_ccb, L2C_FCR_RETX_ALL_PKTS)) {
            osi_free(p_buf);
            return;
        }
    }

#if (L2CAP_ERTM_STATS == TRUE)
    p_ccb->fcrb.ertm_pkt_counts[1]++;
    p_ccb->fcrb.ertm_byte_counts[1] += p_buf->len;
#endif

    /* Extract the sequence number */
    tx_seq = (ctrl_word & L2CAP_FCR_TX_SEQ_BITS) >> L2CAP_FCR_TX_SEQ_BITS_SHIFT;

    /* If we have flow controlled the peer, ignore any bad I-frames from him */
    if ( (tx_seq != p_fcrb->next_seq_expected) && (p_fcrb->local_busy) ) {
        L2CAP_TRACE_WARNING ("Dropping bad I-Frame since we flowed off, tx_seq:%u", tx_seq);
        l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RNR, 0);
        osi_free(p_buf);
        return;
    }

    /* Check if tx-sequence is the expected one */
    if (tx_seq != p_fcrb->next_seq_expected) {
        num_lost = (tx_seq - p_fcrb->next_seq_expected) & L2CAP_FCR_SEQ_MODULO;

        /* Is the frame a duplicate ? If so, just drop it */
        if (num_lost >= p_ccb->our_cfg.fcr.tx_win_sz) {
            /* Duplicate - simply drop it */
            L2CAP_TRACE_WARNING ("process_i_frame() Dropping Duplicate Frame tx_seq:%u  ExpectedTxSeq %u", tx_seq, p_fcrb->next_seq_expected);
            osi_free(p_buf);
        } else {
            L2CAP_TRACE_WARNING ("process_i_frame() CID: 0x%04x  Lost: %u  tx_seq:%u  ExpTxSeq %u  Rej: %u  SRej: %u",
                                 p_ccb->local_cid, num_lost, tx_seq, p_fcrb->next_seq_expected, p_fcrb->rej_sent, p_fcrb->srej_sent);

            if (p_fcrb->srej_sent) {
                /* If SREJ sent, save the frame for later processing as long as it is in sequence */
                next_srej = (((BT_HDR *)fixed_queue_try_peek_last(p_fcrb->srej_rcv_hold_q))->layer_specific + 1) & L2CAP_FCR_SEQ_MODULO;

                if ( (tx_seq == next_srej) && (fixed_queue_length(p_fcrb->srej_rcv_hold_q) < p_ccb->our_cfg.fcr.tx_win_sz) ) {
                    /* If user gave us a pool for held rx buffers, use that */
                    /* TODO: Could that happen? Get rid of this code. */
                    if (p_ccb->ertm_info.fcr_rx_buf_size != L2CAP_FCR_RX_BUF_SIZE) {
                        BT_HDR *p_buf2;

                        /* Adjust offset and len so that control word is copied */
                        p_buf->offset -= L2CAP_FCR_OVERHEAD;
                        p_buf->len    += L2CAP_FCR_OVERHEAD;

                        p_buf2 = l2c_fcr_clone_buf (p_buf, p_buf->offset, p_buf->len);

                        if (p_buf2) {
                            osi_free (p_buf);
                            p_buf = p_buf2;
                        }
                        p_buf->offset += L2CAP_FCR_OVERHEAD;
                        p_buf->len -= L2CAP_FCR_OVERHEAD;
                    }
                    L2CAP_TRACE_DEBUG ("process_i_frame() Lost: %u  tx_seq:%u  ExpTxSeq %u  Rej: %u  SRej1",
                                       num_lost, tx_seq, p_fcrb->next_seq_expected, p_fcrb->rej_sent);

                    p_buf->layer_specific = tx_seq;
                    fixed_queue_enqueue(p_fcrb->srej_rcv_hold_q, p_buf, FIXED_QUEUE_MAX_TIMEOUT);
                } else {
                    L2CAP_TRACE_WARNING ("process_i_frame() CID: 0x%04x  frame dropped in Srej Sent next_srej:%u  hold_q.count:%u  win_sz:%u",
                                         p_ccb->local_cid, next_srej, fixed_queue_length(p_fcrb->srej_rcv_hold_q), p_ccb->our_cfg.fcr.tx_win_sz);

                    p_fcrb->rej_after_srej = TRUE;
                    osi_free (p_buf);
                }
            } else if (p_fcrb->rej_sent) {
                L2CAP_TRACE_WARNING ("process_i_frame() CID: 0x%04x  Lost: %u  tx_seq:%u  ExpTxSeq %u  Rej: 1  SRej: %u",
                                     p_ccb->local_cid, num_lost, tx_seq, p_fcrb->next_seq_expected, p_fcrb->srej_sent);

                /* If REJ sent, just drop the frame */
                osi_free (p_buf);
            } else {
                L2CAP_TRACE_DEBUG ("process_i_frame() CID: 0x%04x  tx_seq:%u  ExpTxSeq %u  Rej: %u",
                                   p_ccb->local_cid, tx_seq, p_fcrb->next_seq_expected, p_fcrb->rej_sent);

                /* If only one lost, we will send SREJ, otherwise we will send REJ */
                if (num_lost > 1) {
                    osi_free (p_buf);
                    p_fcrb->rej_sent = TRUE;
                    l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_REJ, 0);
                } else {
                    if (!fixed_queue_is_empty(p_fcrb->srej_rcv_hold_q)) {
                        L2CAP_TRACE_ERROR ("process_i_frame() CID: 0x%04x  sending SREJ tx_seq:%d hold_q.count:%u",
                                             p_ccb->local_cid, tx_seq, fixed_queue_length(p_fcrb->srej_rcv_hold_q));
                    }
                    p_buf->layer_specific = tx_seq;
                    fixed_queue_enqueue(p_fcrb->srej_rcv_hold_q, p_buf, FIXED_QUEUE_MAX_TIMEOUT);
                    p_fcrb->srej_sent = TRUE;
                    l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_SREJ, 0);
                }
                btu_stop_quick_timer (&p_ccb->fcrb.ack_timer);
            }
        }
        return;
    }

    /* Seq number is the next expected. Clear possible reject exception in case it occured */
    p_fcrb->rej_sent = p_fcrb->srej_sent = FALSE;

    /* Adjust the next_seq, so that if the upper layer sends more data in the callback
       context, the received frame is acked by an I-frame. */
    p_fcrb->next_seq_expected = (tx_seq + 1) & L2CAP_FCR_SEQ_MODULO;

    /* If any SAR problem in eRTM mode, spec says disconnect. */
    if (!do_sar_reassembly (p_ccb, p_buf, ctrl_word)) {
        L2CAP_TRACE_WARNING ("process_i_frame() CID: 0x%04x  reassembly failed", p_ccb->local_cid);
        l2cu_disconnect_chnl (p_ccb);
        return;
    }

    /* RR optimization - if peer can still send us more, then start an ACK timer */
    num_to_ack = (p_fcrb->next_seq_expected - p_fcrb->last_ack_sent) & L2CAP_FCR_SEQ_MODULO;

    if ( (num_to_ack < p_ccb->fcrb.max_held_acks) && (!p_fcrb->local_busy) ) {
        delay_ack = TRUE;
    }

    /* We should neve never ack frame if we are not in OPEN state */
    if ((num_to_ack != 0) && p_ccb->in_use && (p_ccb->chnl_state == CST_OPEN)) {
        /* If no frames are awaiting transmission or are held, send an RR or RNR S-frame for ack */
        if (delay_ack) {
            /* If it is the first I frame we did not ack, start ack timer */
            if (!p_ccb->fcrb.ack_timer.in_use) {
                btu_start_quick_timer (&p_ccb->fcrb.ack_timer, BTU_TTYPE_L2CAP_FCR_ACK,
                                       (L2CAP_FCR_ACK_TOUT * QUICK_TIMER_TICKS_PER_SEC) / 1000);
            }
        } else if ((fixed_queue_is_empty(p_ccb->xmit_hold_q) ||
                  l2c_fcr_is_flow_controlled(p_ccb))
                 && fixed_queue_is_empty(p_ccb->fcrb.srej_rcv_hold_q)) {
            if (p_fcrb->local_busy) {
                l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RNR, 0);
            } else {
                l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RR, 0);
            }
        }
    }
}