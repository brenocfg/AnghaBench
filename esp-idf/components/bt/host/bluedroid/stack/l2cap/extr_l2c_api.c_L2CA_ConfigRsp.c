#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* qos_present; void* flush_to_present; void* mtu_present; } ;
struct TYPE_9__ {TYPE_1__ peer_cfg; } ;
typedef  TYPE_2__ tL2C_CCB ;
struct TYPE_10__ {scalar_t__ result; scalar_t__ qos_present; scalar_t__ flush_to_present; scalar_t__ mtu_present; void* fcr_present; int /*<<< orphan*/  fcs_present; } ;
typedef  TYPE_3__ tL2CAP_CFG_INFO ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ L2CAP_CFG_OK ; 
 scalar_t__ L2CAP_CFG_PENDING ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CEVT_L2CA_CONFIG_RSP ; 
 int /*<<< orphan*/  L2CEVT_L2CA_CONFIG_RSP_NEG ; 
 void* TRUE ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_ConfigRsp (UINT16 cid, tL2CAP_CFG_INFO *p_cfg)
{
    tL2C_CCB        *p_ccb;

    //counter_add("l2cap.cfg.rsp", 1);
    L2CAP_TRACE_API ("L2CA_ConfigRsp()  CID: 0x%04x  Result: %d MTU present:%d Flush TO:%d FCR:%d FCS:%d",
                     cid, p_cfg->result, p_cfg->mtu_present, p_cfg->flush_to_present, p_cfg->fcr_present, p_cfg->fcs_present);

    /* Find the channel control block. We don't know the link it is on. */
    if ((p_ccb = l2cu_find_ccb_by_cid (NULL, cid)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - no CCB for L2CA_cfg_rsp, CID: %d", cid);
        return (FALSE);
    }

    if ( (p_cfg->result == L2CAP_CFG_OK) || (p_cfg->result == L2CAP_CFG_PENDING) ) {
        l2c_csm_execute (p_ccb, L2CEVT_L2CA_CONFIG_RSP, p_cfg);
    } else {
        p_cfg->fcr_present = FALSE; /* FCR options already negotiated before this point */

        /* Clear out any cached options that are being returned as an error (excluding FCR) */
        if (p_cfg->mtu_present) {
            p_ccb->peer_cfg.mtu_present = FALSE;
        }
        if (p_cfg->flush_to_present) {
            p_ccb->peer_cfg.flush_to_present = FALSE;
        }
        if (p_cfg->qos_present) {
            p_ccb->peer_cfg.qos_present = FALSE;
        }

        l2c_csm_execute (p_ccb, L2CEVT_L2CA_CONFIG_RSP_NEG, p_cfg);
    }

    return (TRUE);
}