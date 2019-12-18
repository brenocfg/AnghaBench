#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * ertm_byte_counts; int /*<<< orphan*/ * ertm_pkt_counts; int /*<<< orphan*/  waiting_for_ack_q; int /*<<< orphan*/  pkts_retransmitted; int /*<<< orphan*/  retrans_q; } ;
struct TYPE_13__ {scalar_t__ mode; } ;
struct TYPE_14__ {TYPE_1__ fcr; } ;
struct TYPE_16__ {scalar_t__ tx_mps; scalar_t__ local_cid; scalar_t__ remote_cid; scalar_t__ bypass_fcs; TYPE_3__ fcrb; TYPE_2__ peer_cfg; int /*<<< orphan*/  xmit_hold_q; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_17__ {scalar_t__ event; int len; scalar_t__ offset; int /*<<< orphan*/  layer_specific; } ;
typedef  TYPE_5__ BT_HDR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 scalar_t__ HCI_DATA_PREAMBLE_SIZE ; 
 scalar_t__ L2CAP_BYPASS_FCS ; 
 int /*<<< orphan*/  L2CAP_FCR_CONT_SDU ; 
 int /*<<< orphan*/  L2CAP_FCR_END_SDU ; 
 scalar_t__ L2CAP_FCR_ERTM_MODE ; 
 scalar_t__ L2CAP_FCR_OVERHEAD ; 
 int /*<<< orphan*/  L2CAP_FCR_START_SDU ; 
 int /*<<< orphan*/  L2CAP_FCR_UNSEG_SDU ; 
 int L2CAP_FCS_LEN ; 
 scalar_t__ L2CAP_MAX_HEADER_FCS ; 
 scalar_t__ L2CAP_MIN_OFFSET ; 
 scalar_t__ L2CAP_PKT_OVERHEAD ; 
 scalar_t__ L2CAP_SDU_LEN_OFFSET ; 
 scalar_t__ L2CAP_SDU_LEN_OVERHEAD ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,scalar_t__,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UINT32_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_try_peek_first (int /*<<< orphan*/ ) ; 
 TYPE_5__* l2c_fcr_clone_buf (TYPE_5__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  osi_time_get_os_boottime_ms () ; 
 int /*<<< orphan*/  prepare_I_frame (TYPE_4__*,TYPE_5__*,scalar_t__) ; 

BT_HDR *l2c_fcr_get_next_xmit_sdu_seg (tL2C_CCB *p_ccb, UINT16 max_packet_length)
{
    assert(p_ccb != NULL);

    BOOLEAN     first_seg    = FALSE,       /* The segment is the first part of data  */
                mid_seg      = FALSE,       /* The segment is the middle part of data */
                last_seg     = FALSE;       /* The segment is the last part of data   */
    UINT16      sdu_len = 0;
    BT_HDR      *p_buf, *p_xmit;
    UINT8       *p;
    UINT16      max_pdu = p_ccb->tx_mps /* Needed? - L2CAP_MAX_HEADER_FCS*/;

    /* If there is anything in the retransmit queue, that goes first
    */
    p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->fcrb.retrans_q, 0);
    if (p_buf != NULL) {
        /* Update Rx Seq and FCS if we acked some packets while this one was queued */
        prepare_I_frame (p_ccb, p_buf, TRUE);

        p_buf->event = p_ccb->local_cid;

#if (L2CAP_ERTM_STATS == TRUE)
        p_ccb->fcrb.pkts_retransmitted++;
        p_ccb->fcrb.ertm_pkt_counts[0]++;
        p_ccb->fcrb.ertm_byte_counts[0] += (p_buf->len - 8);
#endif
        return (p_buf);
    }

    /* For BD/EDR controller, max_packet_length is set to 0             */
    /* For AMP controller, max_packet_length is set by available blocks */
    if ( (max_packet_length > L2CAP_MAX_HEADER_FCS)
            && (max_pdu + L2CAP_MAX_HEADER_FCS > max_packet_length) ) {
        max_pdu = max_packet_length - L2CAP_MAX_HEADER_FCS;
    }

    p_buf = (BT_HDR *)fixed_queue_try_peek_first(p_ccb->xmit_hold_q);

    /* If there is more data than the MPS, it requires segmentation */
    if (p_buf->len > max_pdu) {
        /* We are using the "event" field to tell is if we already started segmentation */
        if (p_buf->event == 0) {
            first_seg = TRUE;
            sdu_len   = p_buf->len;
        } else {
            mid_seg = TRUE;
        }

        /* Get a new buffer and copy the data that can be sent in a PDU */
        p_xmit = l2c_fcr_clone_buf (p_buf, L2CAP_MIN_OFFSET + L2CAP_SDU_LEN_OFFSET,
                                    max_pdu);

        if (p_xmit != NULL) {
            p_buf->event  = p_ccb->local_cid;
            p_xmit->event = p_ccb->local_cid;

            p_buf->len    -= max_pdu;
            p_buf->offset += max_pdu;

            /* copy PBF setting */
            p_xmit->layer_specific = p_buf->layer_specific;
        } else { /* Should never happen if the application has configured buffers correctly */
            L2CAP_TRACE_ERROR ("L2CAP - cannot get buffer for segmentation, max_pdu: %u", max_pdu);
            return (NULL);
        }
    } else { /* Use the original buffer if no segmentation, or the last segment */
        p_xmit = (BT_HDR *)fixed_queue_dequeue(p_ccb->xmit_hold_q, 0);

        if (p_xmit->event != 0) {
            last_seg = TRUE;
        }

        p_xmit->event = p_ccb->local_cid;
    }

    /* Step back to add the L2CAP headers */
    p_xmit->offset -= (L2CAP_PKT_OVERHEAD + L2CAP_FCR_OVERHEAD);
    p_xmit->len    += L2CAP_PKT_OVERHEAD + L2CAP_FCR_OVERHEAD;

    if (first_seg) {
        p_xmit->offset -= L2CAP_SDU_LEN_OVERHEAD;
        p_xmit->len    += L2CAP_SDU_LEN_OVERHEAD;
    }

    /* Set the pointer to the beginning of the data */
    p = (UINT8 *)(p_xmit + 1) + p_xmit->offset;

    /* Now the L2CAP header */

    /* Note: if FCS has to be included then the length is recalculated later */
    UINT16_TO_STREAM (p, p_xmit->len - L2CAP_PKT_OVERHEAD);

    UINT16_TO_STREAM (p, p_ccb->remote_cid);

    if (first_seg) {
        /* Skip control word and add SDU length */
        p += 2;
        UINT16_TO_STREAM (p, sdu_len);

        /* We will store the SAR type in layer-specific */
        /* layer_specific is shared with flushable flag(bits 0-1), don't clear it */
        p_xmit->layer_specific |= L2CAP_FCR_START_SDU;

        first_seg = FALSE;
    } else if (mid_seg) {
        p_xmit->layer_specific |= L2CAP_FCR_CONT_SDU;
    } else if (last_seg) {
        p_xmit->layer_specific |= L2CAP_FCR_END_SDU;
    } else {
        p_xmit->layer_specific |= L2CAP_FCR_UNSEG_SDU;
    }

    prepare_I_frame (p_ccb, p_xmit, FALSE);

    if (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) {
        BT_HDR *p_wack = l2c_fcr_clone_buf (p_xmit, HCI_DATA_PREAMBLE_SIZE, p_xmit->len);

        if (!p_wack) {
            L2CAP_TRACE_ERROR("L2CAP - no buffer for xmit cloning, CID: 0x%04x  Length: %u",
                              p_ccb->local_cid, p_xmit->len);

            /* We will not save the FCS in case we reconfigure and change options */
            if (p_ccb->bypass_fcs != L2CAP_BYPASS_FCS) {
                p_xmit->len -= L2CAP_FCS_LEN;
            }

            /* Pretend we sent it and it got lost */
            fixed_queue_enqueue(p_ccb->fcrb.waiting_for_ack_q, p_xmit, FIXED_QUEUE_MAX_TIMEOUT);
            return (NULL);
        } else {
#if (L2CAP_ERTM_STATS == TRUE)
            /* set timestamp at the end of tx I-frame to get acking delay */
            p = ((UINT8 *) (p_wack + 1)) + p_wack->offset + p_wack->len;
            UINT32_TO_STREAM (p, osi_time_get_os_boottime_ms());
#endif
            /* We will not save the FCS in case we reconfigure and change options */
            if (p_ccb->bypass_fcs != L2CAP_BYPASS_FCS) {
                p_wack->len -= L2CAP_FCS_LEN;
            }

            p_wack->layer_specific = p_xmit->layer_specific;
            fixed_queue_enqueue(p_ccb->fcrb.waiting_for_ack_q, p_wack, FIXED_QUEUE_MAX_TIMEOUT);
        }

#if (L2CAP_ERTM_STATS == TRUE)
        p_ccb->fcrb.ertm_pkt_counts[0]++;
        p_ccb->fcrb.ertm_byte_counts[0] += (p_xmit->len - 8);
#endif

    }

    return (p_xmit);
}