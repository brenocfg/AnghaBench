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
struct TYPE_4__ {int /*<<< orphan*/  gap_handle; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GAP_EVT_CONN_CLOSED ; 
 int /*<<< orphan*/  GAP_TRACE_EVENT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CA_DISCONNECT_RSP (int /*<<< orphan*/ ) ; 
 TYPE_1__* gap_find_ccb_by_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gap_release_ccb (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_disconnect_ind (UINT16 l2cap_cid, BOOLEAN ack_needed)
{
    tGAP_CCB    *p_ccb;

    GAP_TRACE_EVENT ("GAP_CONN - Rcvd L2CAP disc, CID: 0x%x", l2cap_cid);

    /* Find CCB based on CID */
    if ((p_ccb = gap_find_ccb_by_cid (l2cap_cid)) == NULL) {
        return;
    }

    if (ack_needed) {
        L2CA_DISCONNECT_RSP (l2cap_cid);
    }

    p_ccb->p_callback (p_ccb->gap_handle, GAP_EVT_CONN_CLOSED);
    gap_release_ccb (p_ccb);
}