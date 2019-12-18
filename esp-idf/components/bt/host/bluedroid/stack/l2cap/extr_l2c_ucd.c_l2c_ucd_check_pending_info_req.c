#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int state; } ;
struct TYPE_16__ {TYPE_1__ ucd; scalar_t__ in_use; } ;
typedef  TYPE_5__ tL2C_RCB ;
struct TYPE_17__ {TYPE_7__* p_lcb; TYPE_4__* p_rcb; } ;
typedef  TYPE_6__ tL2C_CCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_19__ {TYPE_5__* rcb_pool; } ;
struct TYPE_18__ {int info_rx_bits; int peer_ext_fea; scalar_t__ w4_info_rsp; int ucd_mtu; int /*<<< orphan*/  remote_bd_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* pL2CA_UCD_Discover_Cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_14__ {TYPE_2__ cb_info; } ;
struct TYPE_15__ {TYPE_3__ ucd; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int L2CAP_CONNLESS_MTU_INFO_TYPE ; 
 int L2CAP_EXTENDED_FEATURES_INFO_TYPE ; 
 int L2CAP_EXTFEA_UCD_RECEPTION ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  L2CAP_UCD_INFO_TYPE_MTU ; 
 int /*<<< orphan*/  L2CAP_UCD_INFO_TYPE_RECEPTION ; 
 int L2C_UCD_STATE_W4_MTU ; 
 int L2C_UCD_STATE_W4_RECEPTION ; 
 scalar_t__ MAX_L2CAP_CLIENTS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  l2c_ucd_delete_sec_pending_q (TYPE_7__*) ; 
 TYPE_9__ l2cb ; 
 int /*<<< orphan*/  l2cu_release_ccb (TYPE_6__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_info_req (TYPE_7__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

BOOLEAN l2c_ucd_check_pending_info_req(tL2C_CCB  *p_ccb)
{
    tL2C_RCB    *p_rcb = &l2cb.rcb_pool[0];
    UINT16      xx;
    BOOLEAN     pending = FALSE;

    if (p_ccb == NULL) {
        L2CAP_TRACE_ERROR ("L2CAP - NULL p_ccb in l2c_ucd_check_pending_info_req");
        return (FALSE);
    }

    for (xx = 0; xx < MAX_L2CAP_CLIENTS; xx++, p_rcb++) {
        if (p_rcb->in_use) {
            /* if application is waiting UCD reception info */
            if (p_rcb->ucd.state & L2C_UCD_STATE_W4_RECEPTION) {
                /* if this information is available */
                if ( p_ccb->p_lcb->info_rx_bits & (1 << L2CAP_EXTENDED_FEATURES_INFO_TYPE) ) {
                    if (!(p_ccb->p_lcb->peer_ext_fea & L2CAP_EXTFEA_UCD_RECEPTION)) {
                        L2CAP_TRACE_WARNING ("L2CAP - UCD is not supported by peer, l2c_ucd_check_pending_info_req");

                        l2c_ucd_delete_sec_pending_q(p_ccb->p_lcb);
                        l2cu_release_ccb (p_ccb);
                    }

                    p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Discover_Cb (p_ccb->p_lcb->remote_bd_addr,
                            L2CAP_UCD_INFO_TYPE_RECEPTION,
                            p_ccb->p_lcb->peer_ext_fea & L2CAP_EXTFEA_UCD_RECEPTION);
                } else {
                    pending = TRUE;
                    if (p_ccb->p_lcb->w4_info_rsp == FALSE) {
                        l2cu_send_peer_info_req (p_ccb->p_lcb, L2CAP_EXTENDED_FEATURES_INFO_TYPE);
                    }
                }
            }

            /* if application is waiting for UCD MTU */
            if (p_rcb->ucd.state & L2C_UCD_STATE_W4_MTU) {
                /* if this information is available */
                if ( p_ccb->p_lcb->info_rx_bits & (1 << L2CAP_CONNLESS_MTU_INFO_TYPE)) {
                    p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Discover_Cb (p_ccb->p_lcb->remote_bd_addr,
                            L2CAP_UCD_INFO_TYPE_MTU,
                            p_ccb->p_lcb->ucd_mtu);
                } else {
                    pending = TRUE;
                    if (p_ccb->p_lcb->w4_info_rsp == FALSE) {
                        l2cu_send_peer_info_req (p_ccb->p_lcb, L2CAP_CONNLESS_MTU_INFO_TYPE);
                    }
                }
            }
        }
    }
    return (pending);
}