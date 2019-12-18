#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ in_use; } ;
struct TYPE_14__ {size_t next_tx_seq; size_t next_seq_expected; size_t last_ack_sent; TYPE_10__ ack_timer; scalar_t__ send_f_rsp; } ;
typedef  TYPE_3__ tL2C_FCRB ;
struct TYPE_12__ {scalar_t__ mode; } ;
struct TYPE_13__ {TYPE_1__ fcr; } ;
struct TYPE_15__ {scalar_t__ bypass_fcs; TYPE_2__ peer_cfg; int /*<<< orphan*/  local_cid; TYPE_3__ fcrb; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_16__ {int offset; size_t layer_specific; int len; } ;
typedef  TYPE_5__ BT_HDR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ L2CAP_BYPASS_FCS ; 
 scalar_t__ L2CAP_FCR_ERTM_MODE ; 
 size_t L2CAP_FCR_F_BIT ; 
 size_t L2CAP_FCR_F_BIT_SHIFT ; 
 size_t L2CAP_FCR_REQ_SEQ_BITS ; 
 size_t L2CAP_FCR_REQ_SEQ_BITS_SHIFT ; 
 size_t L2CAP_FCR_SAR_BITS ; 
 size_t L2CAP_FCR_SAR_BITS_SHIFT ; 
 size_t L2CAP_FCR_SEG_BITS ; 
 int L2CAP_FCR_SEQ_MODULO ; 
 size_t L2CAP_FCR_TX_SEQ_BITS ; 
 size_t L2CAP_FCR_TX_SEQ_BITS_SHIFT ; 
 int L2CAP_FCS_LEN ; 
 int L2CAP_PKT_OVERHEAD ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,size_t,size_t) ; 
 int /*<<< orphan*/ * SAR_types ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_quick_timer (TYPE_10__*) ; 
 int /*<<< orphan*/  l2c_fcr_start_timer (TYPE_4__*) ; 
 size_t l2c_fcr_tx_get_fcs (TYPE_5__*) ; 

__attribute__((used)) static void prepare_I_frame (tL2C_CCB *p_ccb, BT_HDR *p_buf, BOOLEAN is_retransmission)
{
    assert(p_ccb != NULL);
    assert(p_buf != NULL);
    tL2C_FCRB   *p_fcrb = &p_ccb->fcrb;
    UINT8       *p;
    UINT16      fcs;
    UINT16      ctrl_word;
    BOOLEAN     set_f_bit = p_fcrb->send_f_rsp;

    p_fcrb->send_f_rsp = FALSE;

    if (is_retransmission) {
        /* Get the old control word and clear out the old req_seq and F bits */
        p = ((UINT8 *) (p_buf + 1)) + p_buf->offset + L2CAP_PKT_OVERHEAD;

        STREAM_TO_UINT16 (ctrl_word, p);

        ctrl_word  &= ~(L2CAP_FCR_REQ_SEQ_BITS + L2CAP_FCR_F_BIT);
    } else {
        ctrl_word  = p_buf->layer_specific & L2CAP_FCR_SEG_BITS;                /* SAR bits */
        ctrl_word |= (p_fcrb->next_tx_seq << L2CAP_FCR_TX_SEQ_BITS_SHIFT);      /* Tx Seq */

        p_fcrb->next_tx_seq = (p_fcrb->next_tx_seq + 1) & L2CAP_FCR_SEQ_MODULO;
    }

    /* Set the F-bit and reqseq only if using re-transmission mode */
    if (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) {
        if (set_f_bit) {
            ctrl_word |= L2CAP_FCR_F_BIT;
        }

        ctrl_word |= (p_fcrb->next_seq_expected) << L2CAP_FCR_REQ_SEQ_BITS_SHIFT;

        p_fcrb->last_ack_sent = p_ccb->fcrb.next_seq_expected;

        if (p_ccb->fcrb.ack_timer.in_use) {
            btu_stop_quick_timer (&p_ccb->fcrb.ack_timer);
        }
    }

    /* Set the control word */
    p = ((UINT8 *) (p_buf + 1)) + p_buf->offset + L2CAP_PKT_OVERHEAD;

    UINT16_TO_STREAM (p, ctrl_word);

    /* Compute the FCS and add to the end of the buffer if not bypassed */
    if (p_ccb->bypass_fcs != L2CAP_BYPASS_FCS) {
        /* length field in l2cap header has to include FCS length */
        p = ((UINT8 *) (p_buf + 1)) + p_buf->offset;
        UINT16_TO_STREAM (p, p_buf->len + L2CAP_FCS_LEN - L2CAP_PKT_OVERHEAD);

        /* Calculate the FCS */
        fcs = l2c_fcr_tx_get_fcs(p_buf);

        /* Point to the end of the buffer and put the FCS there */
        p = ((UINT8 *) (p_buf + 1)) + p_buf->offset + p_buf->len;

        UINT16_TO_STREAM (p, fcs);

        p_buf->len += L2CAP_FCS_LEN;
    }

#if BT_TRACE_VERBOSE == TRUE
    if (is_retransmission) {
        L2CAP_TRACE_EVENT ("L2CAP eRTM ReTx I-frame  CID: 0x%04x  Len: %u  SAR: %s  TxSeq: %u  ReqSeq: %u  F: %u",
                           p_ccb->local_cid, p_buf->len,
                           SAR_types[(ctrl_word & L2CAP_FCR_SAR_BITS) >> L2CAP_FCR_SAR_BITS_SHIFT],
                           (ctrl_word & L2CAP_FCR_TX_SEQ_BITS) >> L2CAP_FCR_TX_SEQ_BITS_SHIFT,
                           (ctrl_word & L2CAP_FCR_REQ_SEQ_BITS) >> L2CAP_FCR_REQ_SEQ_BITS_SHIFT,
                           (ctrl_word & L2CAP_FCR_F_BIT) >> L2CAP_FCR_F_BIT_SHIFT);
    } else {
        L2CAP_TRACE_EVENT ("L2CAP eRTM Tx I-frame CID: 0x%04x  Len: %u  SAR: %-12s  TxSeq: %u  ReqSeq: %u  F: %u",
                           p_ccb->local_cid, p_buf->len,
                           SAR_types[(ctrl_word & L2CAP_FCR_SAR_BITS) >> L2CAP_FCR_SAR_BITS_SHIFT],
                           (ctrl_word & L2CAP_FCR_TX_SEQ_BITS) >> L2CAP_FCR_TX_SEQ_BITS_SHIFT,
                           (ctrl_word & L2CAP_FCR_REQ_SEQ_BITS) >> L2CAP_FCR_REQ_SEQ_BITS_SHIFT,
                           (ctrl_word & L2CAP_FCR_F_BIT) >> L2CAP_FCR_F_BIT_SHIFT);
    }
#endif

    /* Start the retransmission timer if not already running */
    if (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) {
        l2c_fcr_start_timer (p_ccb);
    }
}