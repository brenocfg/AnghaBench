#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ con_state; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  con_flags; } ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  GAP_CCB_FLAGS_SEC_DONE ; 
 scalar_t__ GAP_CCB_STATE_IDLE ; 
 int /*<<< orphan*/  GAP_TRACE_EVENT (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CA_DISCONNECT_REQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gap_checks_con_flags (TYPE_1__*) ; 

__attribute__((used)) static void gap_sec_check_complete (BD_ADDR bd_addr, tBT_TRANSPORT transport, void *p_ref_data, UINT8 res)
{
    tGAP_CCB *p_ccb = (tGAP_CCB *)p_ref_data;
    UNUSED(bd_addr);
    UNUSED (transport);

    GAP_TRACE_EVENT ("gap_sec_check_complete conn_state:%d, conn_flags:0x%x, status:%d",
                     p_ccb->con_state, p_ccb->con_flags, res);
    if (p_ccb->con_state == GAP_CCB_STATE_IDLE) {
        return;
    }

    if (res == BTM_SUCCESS) {
        p_ccb->con_flags |= GAP_CCB_FLAGS_SEC_DONE;
        gap_checks_con_flags (p_ccb);
    } else {
        /* security failed - disconnect the channel */
        L2CA_DISCONNECT_REQ (p_ccb->connection_id);
    }
}