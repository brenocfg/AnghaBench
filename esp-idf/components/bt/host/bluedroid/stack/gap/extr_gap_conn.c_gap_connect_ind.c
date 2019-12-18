#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ con_state; scalar_t__ psm; scalar_t__ rem_addr_specified; int /*<<< orphan*/  cfg; scalar_t__ connection_id; int /*<<< orphan*/  ertm_info; int /*<<< orphan*/ * rem_dev_address; } ;
typedef  TYPE_2__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {TYPE_2__* ccb_pool; } ;
struct TYPE_6__ {TYPE_1__ conn; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ FALSE ; 
 scalar_t__ GAP_CCB_STATE_CFG_SETUP ; 
 scalar_t__ GAP_CCB_STATE_LISTENING ; 
 scalar_t__ GAP_MAX_CONNECTIONS ; 
 int /*<<< orphan*/  GAP_TRACE_EVENT (char*,scalar_t__) ; 
 int /*<<< orphan*/  GAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  L2CAP_CONN_OK ; 
 int /*<<< orphan*/  L2CA_CONFIG_REQ (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L2CA_CONNECT_RSP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L2CA_DISCONNECT_REQ (scalar_t__) ; 
 int /*<<< orphan*/  bt_uuid ; 
 TYPE_3__ gap_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_connect_ind (BD_ADDR  bd_addr, UINT16 l2cap_cid, UINT16 psm, UINT8 l2cap_id)
{
    UINT16       xx;
    tGAP_CCB     *p_ccb;
    //tBT_UUID    bt_uuid = {2, {GAP_PROTOCOL_ID}};

    /* See if we have a CCB listening for the connection */
    for (xx = 0, p_ccb = gap_cb.conn.ccb_pool; xx < GAP_MAX_CONNECTIONS; xx++, p_ccb++) {
        if ((p_ccb->con_state == GAP_CCB_STATE_LISTENING)
                && (p_ccb->psm == psm)
                && ((p_ccb->rem_addr_specified == FALSE)
                    || (!memcmp (bd_addr, p_ccb->rem_dev_address, BD_ADDR_LEN)))) {
            break;
        }
    }

    if (xx == GAP_MAX_CONNECTIONS) {
        GAP_TRACE_WARNING("*******");
        GAP_TRACE_WARNING("WARNING: GAP Conn Indication for Unexpected Bd Addr...Disconnecting");
        GAP_TRACE_WARNING("*******");

        /* Disconnect because it is an unexpected connection */
        L2CA_DISCONNECT_REQ (l2cap_cid);
        return;
    }

    /* Transition to the next appropriate state, waiting for config setup. */
    p_ccb->con_state = GAP_CCB_STATE_CFG_SETUP;

    /* Save the BD Address and Channel ID. */
    memcpy (&p_ccb->rem_dev_address[0], bd_addr, BD_ADDR_LEN);
    p_ccb->connection_id = l2cap_cid;

    /* Send response to the L2CAP layer. */
    L2CA_CONNECT_RSP (bd_addr, l2cap_id, l2cap_cid, L2CAP_CONN_OK, L2CAP_CONN_OK, &p_ccb->ertm_info, &bt_uuid);

    GAP_TRACE_EVENT("GAP_CONN - Rcvd L2CAP conn ind, CID: 0x%x", p_ccb->connection_id);

    /* Send a Configuration Request. */
    L2CA_CONFIG_REQ (l2cap_cid, &p_ccb->cfg);
}