#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int mode; scalar_t__ rtrans_tout; scalar_t__ mon_tout; scalar_t__ mps; scalar_t__ tx_win_sz; scalar_t__ max_transmit; } ;
struct TYPE_15__ {scalar_t__ fcs; scalar_t__ mtu; TYPE_6__ fcr; } ;
struct TYPE_14__ {int preferred_mode; int allowed_modes; int fcr_tx_buf_size; } ;
struct TYPE_12__ {int mode; scalar_t__ mps; scalar_t__ mon_tout; scalar_t__ rtrans_tout; scalar_t__ max_transmit; scalar_t__ tx_win_sz; } ;
struct TYPE_13__ {TYPE_2__ fcr; } ;
struct TYPE_17__ {void* peer_cfg_already_rejected; int /*<<< orphan*/  peer_cfg_bits; TYPE_5__ peer_cfg; void* out_cfg_fcr_present; TYPE_4__ ertm_info; int /*<<< orphan*/  bypass_fcs; TYPE_3__ our_cfg; TYPE_1__* p_lcb; } ;
typedef  TYPE_7__ tL2C_CCB ;
struct TYPE_18__ {scalar_t__ fcs; scalar_t__ fcr_present; TYPE_6__ fcr; scalar_t__ fcs_present; } ;
typedef  TYPE_8__ tL2CAP_CFG_INFO ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_11__ {void* w4_info_rsp; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ L2CAP_CFG_FCS_BYPASS ; 
 int /*<<< orphan*/  L2CAP_CFG_FCS_PEER ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_FCR ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_FCS ; 
 int L2CAP_FCR_BASIC_MODE ; 
 int L2CAP_FCR_CHAN_OPT_ALL_MASK ; 
 int L2CAP_FCR_CHAN_OPT_BASIC ; 
 int L2CAP_FCR_CHAN_OPT_ERTM ; 
 int L2CAP_FCR_ERTM_MODE ; 
 int L2CAP_FCR_STREAM_MODE ; 
 int L2CAP_FCS_LEN ; 
 int L2CAP_MIN_OFFSET ; 
 scalar_t__ L2CAP_PEER_CFG_DISCONNECT ; 
 scalar_t__ L2CAP_PEER_CFG_OK ; 
 scalar_t__ L2CAP_PEER_CFG_UNACCEPTABLE ; 
 int L2CAP_SDU_LEN_OFFSET ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,scalar_t__,int,int,int,int) ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

UINT8 l2c_fcr_process_peer_cfg_req(tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    assert(p_ccb != NULL);
    assert(p_cfg != NULL);

    UINT16 max_retrans_size;
    UINT8  fcr_ok = L2CAP_PEER_CFG_OK;

    p_ccb->p_lcb->w4_info_rsp = FALSE;      /* Handles T61x SonyEricsson Bug in Info Request */

    L2CAP_TRACE_EVENT ("l2c_fcr_process_peer_cfg_req() CFG fcr_present:%d fcr.mode:%d CCB FCR mode:%d preferred: %u allowed:%u",
                       p_cfg->fcr_present, p_cfg->fcr.mode, p_ccb->our_cfg.fcr.mode, p_ccb->ertm_info.preferred_mode,
                       p_ccb->ertm_info.allowed_modes);

    /* If Peer wants basic, we are done (accept it or disconnect) */
    if (p_cfg->fcr.mode == L2CAP_FCR_BASIC_MODE) {
        /* If we do not allow basic, disconnect */
        if ( !(p_ccb->ertm_info.allowed_modes & L2CAP_FCR_CHAN_OPT_BASIC) ) {
            fcr_ok = L2CAP_PEER_CFG_DISCONNECT;
        }
    }

    /* Need to negotiate if our modes are not the same */
    else if (p_cfg->fcr.mode != p_ccb->ertm_info.preferred_mode) {
        /* If peer wants a mode that we don't support then retry our mode (ex. rtx/flc), OR
        ** If we want ERTM and they wanted streaming retry our mode.
        ** Note: If we have already determined they support our mode previously
        **       from their EXF mask.
        */
        if ( (((1 << p_cfg->fcr.mode) & L2CAP_FCR_CHAN_OPT_ALL_MASK) == 0)
                || (p_ccb->ertm_info.preferred_mode == L2CAP_FCR_ERTM_MODE) ) {
            p_cfg->fcr.mode = p_ccb->our_cfg.fcr.mode;
            p_cfg->fcr.tx_win_sz = p_ccb->our_cfg.fcr.tx_win_sz;
            p_cfg->fcr.max_transmit = p_ccb->our_cfg.fcr.max_transmit;
            fcr_ok = L2CAP_PEER_CFG_UNACCEPTABLE;
        }

        /* If we wanted basic, then try to renegotiate it */
        else if (p_ccb->ertm_info.preferred_mode == L2CAP_FCR_BASIC_MODE) {
            p_cfg->fcr.mode = L2CAP_FCR_BASIC_MODE;
            p_cfg->fcr.max_transmit = p_cfg->fcr.tx_win_sz = 0;
            p_cfg->fcr.rtrans_tout = p_cfg->fcr.mon_tout = p_cfg->fcr.mps = 0;
            p_ccb->our_cfg.fcr.rtrans_tout = p_ccb->our_cfg.fcr.mon_tout = p_ccb->our_cfg.fcr.mps = 0;
            fcr_ok = L2CAP_PEER_CFG_UNACCEPTABLE;
        }

        /* Only other valid case is if they want ERTM and we wanted STM which should be
           accepted if we support it; otherwise the channel should be disconnected */
        else if ( (p_cfg->fcr.mode != L2CAP_FCR_ERTM_MODE)
                  || !(p_ccb->ertm_info.allowed_modes & L2CAP_FCR_CHAN_OPT_ERTM) ) {
            fcr_ok = L2CAP_PEER_CFG_DISCONNECT;
        }
    }

    /* Configuration for FCR channels so make any adjustments and fwd to upper layer */
    if (fcr_ok == L2CAP_PEER_CFG_OK) {
        /* by default don't need to send params in the response */
        p_ccb->out_cfg_fcr_present = FALSE;

        /* Make any needed adjustments for the response to the peer */
        if (p_cfg->fcr_present && p_cfg->fcr.mode != L2CAP_FCR_BASIC_MODE) {
            /* Peer desires to bypass FCS check, and streaming or ERTM mode */
            if (p_cfg->fcs_present) {
                p_ccb->peer_cfg.fcs = p_cfg->fcs;
                p_ccb->peer_cfg_bits |= L2CAP_CH_CFG_MASK_FCS;
                if ( p_cfg->fcs == L2CAP_CFG_FCS_BYPASS) {
                    p_ccb->bypass_fcs |= L2CAP_CFG_FCS_PEER;
                }
            }

            max_retrans_size = p_ccb->ertm_info.fcr_tx_buf_size - sizeof(BT_HDR)
                               - L2CAP_MIN_OFFSET - L2CAP_SDU_LEN_OFFSET - L2CAP_FCS_LEN;

            /* Ensure the MPS is not bigger than the MTU */
            if ( (p_cfg->fcr.mps == 0) || (p_cfg->fcr.mps > p_ccb->peer_cfg.mtu) ) {
                p_cfg->fcr.mps = p_ccb->peer_cfg.mtu;
                p_ccb->out_cfg_fcr_present = TRUE;
            }

            /* Ensure the MPS is not bigger than our retransmission buffer */
            if (p_cfg->fcr.mps > max_retrans_size) {
                L2CAP_TRACE_DEBUG("CFG: Overriding MPS to %d (orig %d)", max_retrans_size, p_cfg->fcr.mps);

                p_cfg->fcr.mps = max_retrans_size;
                p_ccb->out_cfg_fcr_present = TRUE;
            }

            if (p_cfg->fcr.mode == L2CAP_FCR_ERTM_MODE || p_cfg->fcr.mode == L2CAP_FCR_STREAM_MODE) {
                /* Always respond with FCR ERTM parameters */
                p_ccb->out_cfg_fcr_present = TRUE;
            }
        }

        /* Everything ok, so save the peer's adjusted fcr options */
        p_ccb->peer_cfg.fcr = p_cfg->fcr;

        if (p_cfg->fcr_present) {
            p_ccb->peer_cfg_bits |= L2CAP_CH_CFG_MASK_FCR;
        }
    } else if (fcr_ok == L2CAP_PEER_CFG_UNACCEPTABLE) {
        /* Allow peer only one retry for mode */
        if (p_ccb->peer_cfg_already_rejected) {
            fcr_ok = L2CAP_PEER_CFG_DISCONNECT;
        } else {
            p_ccb->peer_cfg_already_rejected = TRUE;
        }
    }

    return (fcr_ok);
}