#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ mode; } ;
struct TYPE_18__ {TYPE_3__ fcr; void* ext_flow_spec_present; void* fcs_present; void* fcr_present; } ;
struct TYPE_14__ {int allowed_modes; } ;
struct TYPE_16__ {int config_done; scalar_t__ fcr_cfg_tries; TYPE_7__ our_cfg; int /*<<< orphan*/  timer_entry; TYPE_2__ ertm_info; } ;
typedef  TYPE_4__ tL2C_CCB ;
struct TYPE_13__ {void* mode; } ;
struct TYPE_17__ {scalar_t__ result; scalar_t__ mtu; scalar_t__ mtu_present; TYPE_1__ fcr; scalar_t__ fcr_present; } ;
typedef  TYPE_5__ tL2CAP_CFG_INFO ;
typedef  scalar_t__ UINT8 ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_CHNL ; 
 void* FALSE ; 
 scalar_t__ L2CAP_CFG_FAILED_NO_REASON ; 
 scalar_t__ L2CAP_CFG_UNACCEPTABLE_PARAMS ; 
 int /*<<< orphan*/  L2CAP_CHNL_CFG_TIMEOUT ; 
 void* L2CAP_FCR_BASIC_MODE ; 
 int L2CAP_FCR_CHAN_OPT_BASIC ; 
 int L2CAP_FCR_CHAN_OPT_ERTM ; 
#define  L2CAP_FCR_ERTM_MODE 129 
#define  L2CAP_FCR_STREAM_MODE 128 
 scalar_t__ L2CAP_MTU_SIZE ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,...) ; 
 int RECONFIG_FLAG ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_disconnect_chnl (TYPE_4__*) ; 
 int /*<<< orphan*/  l2cu_process_our_cfg_req (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_config_req (TYPE_4__*,TYPE_7__*) ; 

BOOLEAN l2c_fcr_renegotiate_chan(tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    assert(p_ccb != NULL);
    assert(p_cfg != NULL);

    UINT8   peer_mode = p_ccb->our_cfg.fcr.mode;
    BOOLEAN can_renegotiate;

    /* Skip if this is a reconfiguration from OPEN STATE or if FCR is not returned */
    if (!p_cfg->fcr_present || (p_ccb->config_done & RECONFIG_FLAG)) {
        return (FALSE);
    }

    /* Only retry if there are more channel options to try */
    if (p_cfg->result == L2CAP_CFG_UNACCEPTABLE_PARAMS) {
        peer_mode = (p_cfg->fcr_present) ? p_cfg->fcr.mode : L2CAP_FCR_BASIC_MODE;

        if (p_ccb->our_cfg.fcr.mode != peer_mode) {

            if ((--p_ccb->fcr_cfg_tries) == 0) {
                p_cfg->result = L2CAP_CFG_FAILED_NO_REASON;
                L2CAP_TRACE_WARNING ("l2c_fcr_renegotiate_chan (Max retries exceeded)");
            }

            can_renegotiate = FALSE;

            /* Try another supported mode if available based on our last attempted channel */
            switch (p_ccb->our_cfg.fcr.mode) {
            /* Our Streaming mode request was unnacceptable; try ERTM or Basic */
            case L2CAP_FCR_STREAM_MODE:
                /* Peer wants ERTM and we support it */
                if ( (peer_mode == L2CAP_FCR_ERTM_MODE) && (p_ccb->ertm_info.allowed_modes & L2CAP_FCR_CHAN_OPT_ERTM) ) {
                    L2CAP_TRACE_DEBUG ("l2c_fcr_renegotiate_chan(Trying ERTM)");
                    p_ccb->our_cfg.fcr.mode = L2CAP_FCR_ERTM_MODE;
                    can_renegotiate = TRUE;
                } else  /* Falls through */

                case L2CAP_FCR_ERTM_MODE: {
                /* We can try basic for any other peer mode if we support it */
                if (p_ccb->ertm_info.allowed_modes & L2CAP_FCR_CHAN_OPT_BASIC) {
                    L2CAP_TRACE_DEBUG ("l2c_fcr_renegotiate_chan(Trying Basic)");
                    can_renegotiate = TRUE;
                    p_ccb->our_cfg.fcr.mode = L2CAP_FCR_BASIC_MODE;
                }
            }
            break;

            default:
                /* All other scenarios cannot be renegotiated */
                break;
            }

            if (can_renegotiate) {
                p_ccb->our_cfg.fcr_present = TRUE;

                if (p_ccb->our_cfg.fcr.mode == L2CAP_FCR_BASIC_MODE) {
                    p_ccb->our_cfg.fcs_present = FALSE;
                    p_ccb->our_cfg.ext_flow_spec_present = FALSE;

                    /* Basic Mode uses ACL Data Pool, make sure the MTU fits */
                    if ( (p_cfg->mtu_present) && (p_cfg->mtu > L2CAP_MTU_SIZE) ) {
                        L2CAP_TRACE_WARNING ("L2CAP - adjust MTU: %u too large", p_cfg->mtu);
                        p_cfg->mtu = L2CAP_MTU_SIZE;
                    }
                }

                l2cu_process_our_cfg_req (p_ccb, &p_ccb->our_cfg);
                l2cu_send_peer_config_req (p_ccb, &p_ccb->our_cfg);
                btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CFG_TIMEOUT);
                return (TRUE);
            }
        }
    }

    /* Disconnect if the channels do not match */
    if (p_ccb->our_cfg.fcr.mode != peer_mode) {
        L2CAP_TRACE_WARNING ("L2C CFG:  Channels incompatible (local %d, peer %d)",
                             p_ccb->our_cfg.fcr.mode, peer_mode);
        l2cu_disconnect_chnl (p_ccb);
    }

    return (FALSE);
}