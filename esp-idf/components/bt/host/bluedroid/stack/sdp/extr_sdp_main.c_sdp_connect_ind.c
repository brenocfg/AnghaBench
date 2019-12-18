#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mode; int /*<<< orphan*/  mps; int /*<<< orphan*/  mon_tout; int /*<<< orphan*/  rtrans_tout; int /*<<< orphan*/  max_transmit; int /*<<< orphan*/  tx_win_sz; } ;
struct TYPE_8__ {scalar_t__ fcr_present; TYPE_1__ fcr; } ;
typedef  TYPE_2__ tL2CAP_CFG_INFO ;
struct TYPE_9__ {int /*<<< orphan*/  connection_id; int /*<<< orphan*/ * device_address; int /*<<< orphan*/  con_state; } ;
typedef  TYPE_3__ tCONN_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_10__ {TYPE_2__ l2cap_my_cfg; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  L2CAP_CONN_NO_PSM ; 
 int /*<<< orphan*/  L2CAP_CONN_OK ; 
 scalar_t__ L2CAP_FCR_BASIC_MODE ; 
 int /*<<< orphan*/  L2CA_ConfigReq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  L2CA_ConnectRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_STATE_CFG_SETUP ; 
 int /*<<< orphan*/  SDP_TRACE_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_TRACE_EVENT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ sdp_cb ; 
 TYPE_3__* sdpu_allocate_ccb () ; 

__attribute__((used)) static void sdp_connect_ind (BD_ADDR  bd_addr, UINT16 l2cap_cid, UINT16 psm, UINT8 l2cap_id)
{
    UNUSED(psm);
#if SDP_SERVER_ENABLED == TRUE
    tCONN_CB    *p_ccb;

    /* Allocate a new CCB. Return if none available. */
    if ((p_ccb = sdpu_allocate_ccb()) == NULL) {
        return;
    }

    /* Transition to the next appropriate state, waiting for config setup. */
    p_ccb->con_state = SDP_STATE_CFG_SETUP;

    /* Save the BD Address and Channel ID. */
    memcpy (&p_ccb->device_address[0], bd_addr, sizeof (BD_ADDR));
    p_ccb->connection_id = l2cap_cid;

    /* Send response to the L2CAP layer. */
    L2CA_ConnectRsp (bd_addr, l2cap_id, l2cap_cid, L2CAP_CONN_OK, L2CAP_CONN_OK);
    {
        tL2CAP_CFG_INFO cfg = sdp_cb.l2cap_my_cfg;

        if (cfg.fcr_present) {
            SDP_TRACE_DEBUG("sdp_connect_ind:  mode %u, txwinsz %u, max_trans %u, rtrans_tout %u, mon_tout %u, mps %u\n",
                            cfg.fcr.mode, cfg.fcr.tx_win_sz, cfg.fcr.max_transmit,
                            cfg.fcr.rtrans_tout, cfg.fcr.mon_tout, cfg.fcr.mps);
        }

        if ((!L2CA_ConfigReq (l2cap_cid, &cfg)) && cfg.fcr_present
                && cfg.fcr.mode != L2CAP_FCR_BASIC_MODE) {
            /* FCR not desired; try again in basic mode */
            cfg.fcr.mode = L2CAP_FCR_BASIC_MODE;
            cfg.fcr_present = FALSE;
            L2CA_ConfigReq (l2cap_cid, &cfg);
        }
    }

    SDP_TRACE_EVENT ("SDP - Rcvd L2CAP conn ind, sent config req, CID 0x%x\n", p_ccb->connection_id);
#else   /* No server */
    /* Reject the connection */
    L2CA_ConnectRsp (bd_addr, l2cap_id, l2cap_cid, L2CAP_CONN_NO_PSM, 0);
#endif
}