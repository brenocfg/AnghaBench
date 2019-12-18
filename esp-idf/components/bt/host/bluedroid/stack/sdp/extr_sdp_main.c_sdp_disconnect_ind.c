#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ con_state; int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* p_cb2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_cb ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ tCONN_CB ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  L2CA_DisconnectRsp (int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_CONN_FAILED ; 
 scalar_t__ SDP_STATE_CONNECTED ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  SDP_TRACE_EVENT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sdpu_find_ccb_by_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdpu_release_ccb (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdp_disconnect_ind (UINT16 l2cap_cid, BOOLEAN ack_needed)
{
    tCONN_CB    *p_ccb;

    /* Find CCB based on CID */
    if ((p_ccb = sdpu_find_ccb_by_cid (l2cap_cid)) == NULL) {
        SDP_TRACE_WARNING ("SDP - Rcvd L2CAP disc, unknown CID: 0x%x\n", l2cap_cid);
        return;
    }

    if (ack_needed) {
        L2CA_DisconnectRsp (l2cap_cid);
    }

    SDP_TRACE_EVENT ("SDP - Rcvd L2CAP disc, CID: 0x%x\n", l2cap_cid);
#if SDP_CLIENT_ENABLED == TRUE
    /* Tell the user if he has a callback */
    if (p_ccb->p_cb) {
        (*p_ccb->p_cb) ((UINT16) ((p_ccb->con_state == SDP_STATE_CONNECTED) ?
                                  SDP_SUCCESS : SDP_CONN_FAILED));
    } else if (p_ccb->p_cb2) {
        (*p_ccb->p_cb2) ((UINT16) ((p_ccb->con_state == SDP_STATE_CONNECTED) ?
                                   SDP_SUCCESS : SDP_CONN_FAILED), p_ccb->user_data);
    }

#endif
    sdpu_release_ccb (p_ccb);
}