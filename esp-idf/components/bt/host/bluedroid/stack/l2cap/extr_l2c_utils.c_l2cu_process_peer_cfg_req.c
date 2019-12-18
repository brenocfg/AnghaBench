#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ service_type; } ;
struct TYPE_13__ {scalar_t__ mtu; int flush_to; TYPE_2__ qos; void* qos_present; void* flush_to_present; void* mtu_present; } ;
struct TYPE_14__ {TYPE_3__ peer_cfg; int /*<<< orphan*/  peer_cfg_bits; } ;
typedef  TYPE_4__ tL2C_CCB ;
struct TYPE_11__ {int /*<<< orphan*/  mode; } ;
struct TYPE_15__ {scalar_t__ fcr_present; scalar_t__ mtu; int flush_to; void* qos_present; void* flush_to_present; void* mtu_present; int /*<<< orphan*/  result; TYPE_2__ qos; TYPE_1__ fcr; } ;
typedef  TYPE_5__ tL2CAP_CFG_INFO ;
typedef  scalar_t__ UINT8 ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ BEST_EFFORT ; 
 scalar_t__ FALSE ; 
 scalar_t__ GUARANTEED ; 
 int /*<<< orphan*/  L2CAP_CFG_FAILED_NO_REASON ; 
 int /*<<< orphan*/  L2CAP_CFG_UNACCEPTABLE_PARAMS ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_FLUSH_TO ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_MTU ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_QOS ; 
 int /*<<< orphan*/  L2CAP_FCR_BASIC_MODE ; 
 scalar_t__ L2CAP_MIN_MTU ; 
 scalar_t__ L2CAP_MTU_SIZE ; 
 scalar_t__ L2CAP_PEER_CFG_DISCONNECT ; 
 scalar_t__ L2CAP_PEER_CFG_OK ; 
 scalar_t__ L2CAP_PEER_CFG_UNACCEPTABLE ; 
 void* TRUE ; 
 scalar_t__ l2c_fcr_process_peer_cfg_req (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  l2cu_adjust_out_mps (TYPE_4__*) ; 

UINT8 l2cu_process_peer_cfg_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    BOOLEAN  mtu_ok      = TRUE;
    BOOLEAN  qos_type_ok = TRUE;
    BOOLEAN  flush_to_ok = TRUE;
    BOOLEAN  fcr_ok      = TRUE;
#if (CLASSIC_BT_INCLUDED == TRUE)
    UINT8    fcr_status;
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    /* Ignore FCR parameters for basic mode */
    if (!p_cfg->fcr_present) {
        p_cfg->fcr.mode = L2CAP_FCR_BASIC_MODE;
    }

    /* Save the MTU that our peer can receive */
    if (p_cfg->mtu_present) {
        /* Make sure MTU is at least the minimum */
        if (p_cfg->mtu >= L2CAP_MIN_MTU) {
            /* In basic mode, limit the MTU to our buffer size */
            if ( (p_cfg->fcr_present == FALSE) && (p_cfg->mtu > L2CAP_MTU_SIZE) ) {
                p_cfg->mtu = L2CAP_MTU_SIZE;
            }

            /* Save the accepted value in case of renegotiation */
            p_ccb->peer_cfg.mtu = p_cfg->mtu;
            p_ccb->peer_cfg.mtu_present = TRUE;
            p_ccb->peer_cfg_bits |= L2CAP_CH_CFG_MASK_MTU;
        } else { /* Illegal MTU value */
            p_cfg->mtu = L2CAP_MIN_MTU;
            mtu_ok     = FALSE;
        }
    }
    /* Reload mtu from a previously accepted config request */
    else if (p_ccb->peer_cfg.mtu_present) {
        p_cfg->mtu_present = TRUE;
        p_cfg->mtu = p_ccb->peer_cfg.mtu;
    }

    /* Verify that the flush timeout is a valid value (0 is illegal) */
    if (p_cfg->flush_to_present) {
        if (!p_cfg->flush_to) {
            p_cfg->flush_to = 0xFFFF;   /* Infinite retransmissions (spec default) */
            flush_to_ok     = FALSE;
        } else { /* Save the accepted value in case of renegotiation */
            p_ccb->peer_cfg.flush_to_present = TRUE;
            p_ccb->peer_cfg.flush_to = p_cfg->flush_to;
            p_ccb->peer_cfg_bits |= L2CAP_CH_CFG_MASK_FLUSH_TO;
        }
    }
    /* Reload flush_to from a previously accepted config request */
    else if (p_ccb->peer_cfg.flush_to_present) {
        p_cfg->flush_to_present = TRUE;
        p_cfg->flush_to = p_ccb->peer_cfg.flush_to;
    }

    /* Save the QOS settings the the peer is using */
    if (p_cfg->qos_present) {
        /* Make sure service type is not a reserved value; otherwise let upper
           layer decide if acceptable
        */
        if (p_cfg->qos.service_type <= GUARANTEED) {
            p_ccb->peer_cfg.qos         = p_cfg->qos;
            p_ccb->peer_cfg.qos_present = TRUE;
            p_ccb->peer_cfg_bits |= L2CAP_CH_CFG_MASK_QOS;
        } else { /* Illegal service type value */
            p_cfg->qos.service_type = BEST_EFFORT;
            qos_type_ok             = FALSE;
        }
    }
    /* Reload QOS from a previously accepted config request */
    else if (p_ccb->peer_cfg.qos_present) {
        p_cfg->qos_present = TRUE;
        p_cfg->qos         = p_ccb->peer_cfg.qos;
    }
#if (CLASSIC_BT_INCLUDED == TRUE)
    if ((fcr_status = l2c_fcr_process_peer_cfg_req (p_ccb, p_cfg)) == L2CAP_PEER_CFG_DISCONNECT) {
        /* Notify caller to disconnect the channel (incompatible modes) */
        p_cfg->result = L2CAP_CFG_FAILED_NO_REASON;
        p_cfg->mtu_present = p_cfg->qos_present = p_cfg->flush_to_present = 0;

        return (L2CAP_PEER_CFG_DISCONNECT);
    }

    fcr_ok = (fcr_status == L2CAP_PEER_CFG_OK);
#endif  ///CLASSIC_BT_INCLUDED == TRUE

    /* Return any unacceptable parameters */
    if (mtu_ok && flush_to_ok && qos_type_ok && fcr_ok) {
        l2cu_adjust_out_mps (p_ccb);
        return (L2CAP_PEER_CFG_OK);
    } else {
        p_cfg->result = L2CAP_CFG_UNACCEPTABLE_PARAMS;

        if (mtu_ok) {
            p_cfg->mtu_present = FALSE;
        }
        if (flush_to_ok) {
            p_cfg->flush_to_present = FALSE;
        }
        if (qos_type_ok) {
            p_cfg->qos_present = FALSE;
        }
        if (fcr_ok) {
            p_cfg->fcr_present = FALSE;
        }

        return (L2CAP_PEER_CFG_UNACCEPTABLE);
    }
}