#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ext_flow_spec_present; scalar_t__ fcs_present; scalar_t__ fcr_present; scalar_t__ flush_to_present; scalar_t__ qos_present; scalar_t__ mtu_present; } ;
struct TYPE_6__ {int /*<<< orphan*/  peer_cfg_bits; TYPE_2__ peer_cfg; TYPE_2__ our_cfg; } ;
typedef  TYPE_1__ tL2C_CCB ;
typedef  int /*<<< orphan*/  tL2CAP_CH_CFG_BITS ;
typedef  TYPE_2__ tL2CAP_CFG_INFO ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_EXT_FLOW_SPEC ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_FCR ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_FCS ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_FLUSH_TO ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_MTU ; 
 int /*<<< orphan*/  L2CAP_CH_CFG_MASK_QOS ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_GetCurrentConfig (UINT16 lcid,
                               tL2CAP_CFG_INFO **pp_our_cfg,  tL2CAP_CH_CFG_BITS *p_our_cfg_bits,
                               tL2CAP_CFG_INFO **pp_peer_cfg, tL2CAP_CH_CFG_BITS *p_peer_cfg_bits)
{
    tL2C_CCB    *p_ccb;

    L2CAP_TRACE_API ("L2CA_GetCurrentConfig()  CID: 0x%04x", lcid);

    p_ccb = l2cu_find_ccb_by_cid(NULL, lcid);

    if (p_ccb) {
        *pp_our_cfg  = &(p_ccb->our_cfg);

        /* convert valid config items into bitmap */
        *p_our_cfg_bits = 0;
        if (p_ccb->our_cfg.mtu_present) {
            *p_our_cfg_bits |= L2CAP_CH_CFG_MASK_MTU;
        }
        if (p_ccb->our_cfg.qos_present) {
            *p_our_cfg_bits |= L2CAP_CH_CFG_MASK_QOS;
        }
        if (p_ccb->our_cfg.flush_to_present) {
            *p_our_cfg_bits |= L2CAP_CH_CFG_MASK_FLUSH_TO;
        }
        if (p_ccb->our_cfg.fcr_present) {
            *p_our_cfg_bits |= L2CAP_CH_CFG_MASK_FCR;
        }
        if (p_ccb->our_cfg.fcs_present) {
            *p_our_cfg_bits |= L2CAP_CH_CFG_MASK_FCS;
        }
        if (p_ccb->our_cfg.ext_flow_spec_present) {
            *p_our_cfg_bits |= L2CAP_CH_CFG_MASK_EXT_FLOW_SPEC;
        }

        *pp_peer_cfg = &(p_ccb->peer_cfg);
        *p_peer_cfg_bits = p_ccb->peer_cfg_bits;

        return TRUE;
    } else {
        L2CAP_TRACE_ERROR ("No CCB for CID:0x%04x", lcid);
        return FALSE;
    }
}