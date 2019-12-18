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
struct TYPE_4__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* p_cb2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  connection_id; int /*<<< orphan*/  con_state; } ;
typedef  TYPE_1__ tCONN_CB ;

/* Variables and functions */
 int /*<<< orphan*/  L2CA_DisconnectReq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_CONN_FAILED ; 
 int /*<<< orphan*/  SDP_TRACE_EVENT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdpu_release_ccb (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sdp_conn_timeout (tCONN_CB *p_ccb)
{
    SDP_TRACE_EVENT ("SDP - CCB timeout in state: %d  CID: 0x%x\n",
                     p_ccb->con_state, p_ccb->connection_id);

    L2CA_DisconnectReq (p_ccb->connection_id);
#if SDP_CLIENT_ENABLED == TRUE
    /* Tell the user if he has a callback */
    if (p_ccb->p_cb) {
        (*p_ccb->p_cb) (SDP_CONN_FAILED);
    } else if (p_ccb->p_cb2) {
        (*p_ccb->p_cb2) (SDP_CONN_FAILED, p_ccb->user_data);
    }
#endif
    sdpu_release_ccb (p_ccb);
}