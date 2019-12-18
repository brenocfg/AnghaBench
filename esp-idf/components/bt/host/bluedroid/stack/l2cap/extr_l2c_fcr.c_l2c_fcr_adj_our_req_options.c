#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ mode; scalar_t__ mps; } ;
struct TYPE_11__ {void* fcr_present; TYPE_4__ fcr; } ;
struct TYPE_10__ {scalar_t__ preferred_mode; int allowed_modes; } ;
struct TYPE_12__ {int config_done; scalar_t__ max_rx_mtu; TYPE_2__ our_cfg; TYPE_1__ ertm_info; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  TYPE_4__ tL2CAP_FCR_OPTS ;
struct TYPE_14__ {scalar_t__ mtu; void* ext_flow_spec_present; void* fcs_present; scalar_t__ mtu_present; void* fcr_present; TYPE_4__ fcr; } ;
typedef  TYPE_5__ tL2CAP_CFG_INFO ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ L2CAP_DEFAULT_ERM_MPS ; 
 scalar_t__ L2CAP_FCR_BASIC_MODE ; 
 int L2CAP_FCR_CHAN_OPT_BASIC ; 
 int L2CAP_FCR_CHAN_OPT_ERTM ; 
 int L2CAP_FCR_CHAN_OPT_STREAM ; 
 scalar_t__ L2CAP_FCR_ERTM_MODE ; 
 scalar_t__ L2CAP_FCR_STREAM_MODE ; 
 scalar_t__ L2CAP_MAX_HEADER_FCS ; 
 scalar_t__ L2CAP_MPS_OVER_BR_EDR ; 
 scalar_t__ L2CAP_MTU_SIZE ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,scalar_t__,...) ; 
 int RECONFIG_FLAG ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_fcr_chk_chan_modes (TYPE_3__*) ; 
 int /*<<< orphan*/  l2cu_disconnect_chnl (TYPE_3__*) ; 

BOOLEAN l2c_fcr_adj_our_req_options (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    assert(p_ccb != NULL);
    assert(p_cfg != NULL);

    tL2CAP_FCR_OPTS *p_fcr = &p_cfg->fcr;

    if (p_fcr->mode != p_ccb->ertm_info.preferred_mode) {
        L2CAP_TRACE_WARNING ("l2c_fcr_adj_our_req_options - preferred_mode (%d), does not match mode (%d)",
                             p_ccb->ertm_info.preferred_mode, p_fcr->mode);

        /* The preferred mode is passed in through tL2CAP_ERTM_INFO, so override this one */
        p_fcr->mode = p_ccb->ertm_info.preferred_mode;
    }

    /* If upper layer did not request eRTM mode, BASIC must be used */
    if (p_ccb->ertm_info.allowed_modes == L2CAP_FCR_CHAN_OPT_BASIC) {
        if (p_cfg->fcr_present && p_fcr->mode != L2CAP_FCR_BASIC_MODE) {
            L2CAP_TRACE_WARNING ("l2c_fcr_adj_our_req_options (mode %d): ERROR: No FCR options set using BASIC mode", p_fcr->mode);
        }
        p_fcr->mode = L2CAP_FCR_BASIC_MODE;
    }

    /* Process the FCR options if initial channel bring-up (not a reconfig request)
    ** Determine initial channel mode to try based on our options and remote's features
    */
    if (p_cfg->fcr_present && !(p_ccb->config_done & RECONFIG_FLAG)) {
        /* We need to have at least one mode type common with the peer */
        if (!l2c_fcr_chk_chan_modes(p_ccb)) {
            /* Two channels have incompatible supported types */
            l2cu_disconnect_chnl (p_ccb);
            return (FALSE);
        }

        /* Basic is the only common channel mode between the two devices */
        else if (p_ccb->ertm_info.allowed_modes == L2CAP_FCR_CHAN_OPT_BASIC) {
            /* We only want to try Basic, so bypass sending the FCR options entirely */
            p_cfg->fcr_present = FALSE;
            p_cfg->fcs_present = FALSE;             /* Illegal to use FCS option in basic mode */
            p_cfg->ext_flow_spec_present = FALSE;   /* Illegal to use extended flow spec in basic mode */
        }

        /* We have at least one non-basic mode available
         * Override mode from available mode options based on preference, if needed
         */
        else {
            /* If peer does not support STREAMING, try ERTM */
            if (p_fcr->mode == L2CAP_FCR_STREAM_MODE && !(p_ccb->ertm_info.allowed_modes & L2CAP_FCR_CHAN_OPT_STREAM)) {
                L2CAP_TRACE_DEBUG ("L2C CFG: mode is STREAM, but peer does not support; Try ERTM");
                p_fcr->mode = L2CAP_FCR_ERTM_MODE;
            }

            /* If peer does not support ERTM, try BASIC (will support this if made it here in the code) */
            if (p_fcr->mode == L2CAP_FCR_ERTM_MODE && !(p_ccb->ertm_info.allowed_modes & L2CAP_FCR_CHAN_OPT_ERTM)) {
                L2CAP_TRACE_DEBUG ("L2C CFG: mode is ERTM, but peer does not support; Try BASIC");
                p_fcr->mode = L2CAP_FCR_BASIC_MODE;
            }
        }

        if (p_fcr->mode != L2CAP_FCR_BASIC_MODE) {
            /* MTU must be smaller than buffer size */
            if ( (p_cfg->mtu_present) && (p_cfg->mtu > p_ccb->max_rx_mtu) ) {
                L2CAP_TRACE_WARNING ("L2CAP - MTU: %u  larger than buf size: %u", p_cfg->mtu, p_ccb->max_rx_mtu);
                return (FALSE);
            }

            /* application want to use the default MPS */
            if (p_fcr->mps == L2CAP_DEFAULT_ERM_MPS) {
                p_fcr->mps = L2CAP_MPS_OVER_BR_EDR;
            }
            /* MPS must be less than MTU */
            else if (p_fcr->mps > p_ccb->max_rx_mtu) {
                L2CAP_TRACE_WARNING ("L2CAP - MPS  %u  invalid  MTU: %u", p_fcr->mps, p_ccb->max_rx_mtu);
                return (FALSE);
            }

            /* We always initially read into the HCI buffer pool, so make sure it fits */
            if (p_fcr->mps > (L2CAP_MTU_SIZE - L2CAP_MAX_HEADER_FCS)) {
                p_fcr->mps = L2CAP_MTU_SIZE - L2CAP_MAX_HEADER_FCS;
            }
        } else {
            p_cfg->fcs_present = FALSE;             /* Illegal to use FCS option in basic mode */
            p_cfg->ext_flow_spec_present = FALSE;   /* Illegal to use extended flow spec in basic mode */
        }

        p_ccb->our_cfg.fcr = *p_fcr;
    } else { /* Not sure how to send a reconfiguration(??) should fcr be included? */
        p_ccb->our_cfg.fcr_present = FALSE;
    }

    return (TRUE);
}