#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ con_state; int con_flags; } ;
typedef  TYPE_1__ tCONN_CB ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int SDP_FLAGS_IS_ORIG ; 
 scalar_t__ SDP_STATE_CONNECTED ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_disc_server_rsp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_server_handle_client_req (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* sdpu_find_ccb_by_cid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdp_data_ind (UINT16 l2cap_cid, BT_HDR *p_msg)
{
    tCONN_CB    *p_ccb;

    /* Find CCB based on CID */
    if ((p_ccb = sdpu_find_ccb_by_cid (l2cap_cid)) != NULL) {
        if (p_ccb->con_state == SDP_STATE_CONNECTED) {
            if (p_ccb->con_flags & SDP_FLAGS_IS_ORIG) {
                sdp_disc_server_rsp (p_ccb, p_msg);
            } else {
                sdp_server_handle_client_req (p_ccb, p_msg);
            }
        } else {
            SDP_TRACE_WARNING ("SDP - Ignored L2CAP data while in state: %d, CID: 0x%x\n",
                               p_ccb->con_state, l2cap_cid);
        }
    } else {
        SDP_TRACE_WARNING ("SDP - Rcvd L2CAP data, unknown CID: 0x%x\n", l2cap_cid);
    }

    osi_free (p_msg);
}