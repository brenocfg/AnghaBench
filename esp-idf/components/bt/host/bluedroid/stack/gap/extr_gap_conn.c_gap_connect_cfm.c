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
struct TYPE_5__ {int con_flags; scalar_t__ con_state; int /*<<< orphan*/  gap_handle; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cfg; int /*<<< orphan*/  psm; int /*<<< orphan*/  rem_dev_address; } ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int GAP_CCB_FLAGS_SEC_DONE ; 
 scalar_t__ GAP_CCB_STATE_CFG_SETUP ; 
 scalar_t__ GAP_CCB_STATE_CONN_SETUP ; 
 int /*<<< orphan*/  GAP_EVT_CONN_CLOSED ; 
 scalar_t__ L2CAP_CONN_OK ; 
 int /*<<< orphan*/  L2CA_CONFIG_REQ (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_sec_mx_access_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* gap_find_ccb_by_cid (scalar_t__) ; 
 int /*<<< orphan*/  gap_release_ccb (TYPE_1__*) ; 
 int /*<<< orphan*/  gap_sec_check_complete ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_connect_cfm (UINT16 l2cap_cid, UINT16 result)
{
    tGAP_CCB    *p_ccb;

    /* Find CCB based on CID */
    if ((p_ccb = gap_find_ccb_by_cid (l2cap_cid)) == NULL) {
        return;
    }

    /* initiate security process, if needed */
    if ( (p_ccb->con_flags & GAP_CCB_FLAGS_SEC_DONE) == 0) {
        btm_sec_mx_access_request (p_ccb->rem_dev_address, p_ccb->psm, TRUE,
                                   0, 0, &gap_sec_check_complete, p_ccb);
    }

    /* If the connection response contains success status, then */
    /* Transition to the next state and startup the timer.      */
    if ((result == L2CAP_CONN_OK) && (p_ccb->con_state == GAP_CCB_STATE_CONN_SETUP)) {
        p_ccb->con_state = GAP_CCB_STATE_CFG_SETUP;

        /* Send a Configuration Request. */
        L2CA_CONFIG_REQ (l2cap_cid, &p_ccb->cfg);
    } else {
        /* Tell the user if he has a callback */
        if (p_ccb->p_callback) {
            (*p_ccb->p_callback) (p_ccb->gap_handle, GAP_EVT_CONN_CLOSED);
        }

        gap_release_ccb (p_ccb);
    }
}