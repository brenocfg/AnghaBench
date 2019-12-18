#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ mode; int /*<<< orphan*/  mps; int /*<<< orphan*/  mon_tout; int /*<<< orphan*/  rtrans_tout; int /*<<< orphan*/  max_transmit; int /*<<< orphan*/  tx_win_sz; } ;
struct TYPE_9__ {TYPE_1__ fcr; scalar_t__ fcr_present; } ;
typedef  TYPE_2__ tL2CAP_CFG_INFO ;
struct TYPE_10__ {scalar_t__ con_state; int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* p_cb2 ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_cb ) (scalar_t__) ;int /*<<< orphan*/  connection_id; } ;
typedef  TYPE_3__ tCONN_CB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_11__ {TYPE_2__ l2cap_my_cfg; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ HCI_ERR_AUTH_FAILURE ; 
 scalar_t__ HCI_ERR_HOST_REJECT_DEVICE ; 
 scalar_t__ HCI_ERR_HOST_REJECT_SECURITY ; 
 scalar_t__ HCI_ERR_KEY_MISSING ; 
 scalar_t__ HCI_ERR_PAIRING_NOT_ALLOWED ; 
 scalar_t__ HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED ; 
 scalar_t__ L2CAP_CONN_OK ; 
 scalar_t__ L2CAP_FCR_BASIC_MODE ; 
 int /*<<< orphan*/  L2CA_ConfigReq (scalar_t__,TYPE_2__*) ; 
 scalar_t__ SDP_CONN_FAILED ; 
 scalar_t__ SDP_CONN_REJECTED ; 
 scalar_t__ SDP_SECURITY_ERR ; 
 scalar_t__ SDP_STATE_CFG_SETUP ; 
 scalar_t__ SDP_STATE_CONN_SETUP ; 
 int /*<<< orphan*/  SDP_TRACE_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_TRACE_EVENT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,scalar_t__,...) ; 
 TYPE_6__ sdp_cb ; 
 TYPE_3__* sdpu_find_ccb_by_cid (scalar_t__) ; 
 int /*<<< orphan*/  sdpu_release_ccb (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdp_connect_cfm (UINT16 l2cap_cid, UINT16 result)
{
    tCONN_CB    *p_ccb;
    tL2CAP_CFG_INFO cfg;

    /* Find CCB based on CID */
    if ((p_ccb = sdpu_find_ccb_by_cid (l2cap_cid)) == NULL) {
        SDP_TRACE_WARNING ("SDP - Rcvd conn cnf for unknown CID 0x%x\n", l2cap_cid);
        return;
    }

    /* If the connection response contains success status, then */
    /* Transition to the next state and startup the timer.      */
    if ((result == L2CAP_CONN_OK) && (p_ccb->con_state == SDP_STATE_CONN_SETUP)) {
        p_ccb->con_state = SDP_STATE_CFG_SETUP;

        cfg = sdp_cb.l2cap_my_cfg;

        if (cfg.fcr_present) {
            SDP_TRACE_DEBUG("sdp_connect_cfm:  mode %u, txwinsz %u, max_trans %u, rtrans_tout %u, mon_tout %u, mps %u\n",
                            cfg.fcr.mode, cfg.fcr.tx_win_sz, cfg.fcr.max_transmit,
                            cfg.fcr.rtrans_tout, cfg.fcr.mon_tout, cfg.fcr.mps);
        }

        if ((!L2CA_ConfigReq (l2cap_cid, &cfg)) && cfg.fcr_present
                && cfg.fcr.mode != L2CAP_FCR_BASIC_MODE) {
            /* FCR not desired; try again in basic mode */
            cfg.fcr_present = FALSE;
            cfg.fcr.mode = L2CAP_FCR_BASIC_MODE;
            L2CA_ConfigReq (l2cap_cid, &cfg);
        }

        SDP_TRACE_EVENT ("SDP - got conn cnf, sent cfg req, CID: 0x%x\n", p_ccb->connection_id);
    } else {
        SDP_TRACE_WARNING ("SDP - Rcvd conn cnf with error: 0x%x  CID 0x%x\n", result, p_ccb->connection_id);

        /* Tell the user if he has a callback */
        if (p_ccb->p_cb || p_ccb->p_cb2) {
            UINT16 err = -1;
            if ((result == HCI_ERR_HOST_REJECT_SECURITY)
                    || (result == HCI_ERR_AUTH_FAILURE)
                    || (result == HCI_ERR_PAIRING_NOT_ALLOWED)
                    || (result == HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED)
                    || (result == HCI_ERR_KEY_MISSING)) {
                err = SDP_SECURITY_ERR;
            } else if (result == HCI_ERR_HOST_REJECT_DEVICE) {
                err = SDP_CONN_REJECTED;
            } else {
                err = SDP_CONN_FAILED;
            }
            if (p_ccb->p_cb) {
                (*p_ccb->p_cb)(err);
            } else if (p_ccb->p_cb2) {
                (*p_ccb->p_cb2)(err, p_ccb->user_data);
            }

        }
        sdpu_release_ccb (p_ccb);
    }
}