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
struct TYPE_5__ {scalar_t__ connection_id; int /*<<< orphan*/  con_state; int /*<<< orphan*/ * device_address; int /*<<< orphan*/  con_flags; } ;
typedef  TYPE_1__ tCONN_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ L2CA_ConnectReq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDP_FLAGS_IS_ORIG ; 
 int /*<<< orphan*/  SDP_PSM ; 
 int /*<<< orphan*/  SDP_STATE_CONN_SETUP ; 
 int /*<<< orphan*/  SDP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* sdpu_allocate_ccb () ; 
 int /*<<< orphan*/  sdpu_release_ccb (TYPE_1__*) ; 

tCONN_CB *sdp_conn_originate (UINT8 *p_bd_addr)
{
    tCONN_CB              *p_ccb;
    UINT16                cid;

    /* Allocate a new CCB. Return if none available. */
    if ((p_ccb = sdpu_allocate_ccb()) == NULL) {
        SDP_TRACE_WARNING ("SDP - no spare CCB for orig\n");
        return (NULL);
    }

    SDP_TRACE_EVENT ("SDP - Originate started\n");

    /* We are the originator of this connection */
    p_ccb->con_flags |= SDP_FLAGS_IS_ORIG;

    /* Save the BD Address and Channel ID. */
    memcpy (&p_ccb->device_address[0], p_bd_addr, sizeof (BD_ADDR));

    /* Transition to the next appropriate state, waiting for connection confirm. */
    p_ccb->con_state = SDP_STATE_CONN_SETUP;

    cid = L2CA_ConnectReq (SDP_PSM, p_bd_addr);

    /* Check if L2CAP started the connection process */
    if (cid != 0) {
        p_ccb->connection_id = cid;

        return (p_ccb);
    } else {
        SDP_TRACE_WARNING ("SDP - Originate failed\n");
        sdpu_release_ccb (p_ccb);
        return (NULL);
    }
}