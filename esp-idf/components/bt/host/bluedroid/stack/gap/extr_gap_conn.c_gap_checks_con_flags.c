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
struct TYPE_3__ {int con_flags; int /*<<< orphan*/  gap_handle; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  con_state; } ;
typedef  TYPE_1__ tGAP_CCB ;

/* Variables and functions */
 int GAP_CCB_FLAGS_CONN_DONE ; 
 int /*<<< orphan*/  GAP_CCB_STATE_CONNECTED ; 
 int /*<<< orphan*/  GAP_EVT_CONN_OPENED ; 
 int /*<<< orphan*/  GAP_TRACE_EVENT (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_checks_con_flags (tGAP_CCB    *p_ccb)
{
    GAP_TRACE_EVENT ("gap_checks_con_flags conn_flags:0x%x, ", p_ccb->con_flags);
    /* if all the required con_flags are set, report the OPEN event now */
    if ((p_ccb->con_flags & GAP_CCB_FLAGS_CONN_DONE) == GAP_CCB_FLAGS_CONN_DONE) {
        p_ccb->con_state = GAP_CCB_STATE_CONNECTED;

        p_ccb->p_callback (p_ccb->gap_handle, GAP_EVT_CONN_OPENED);
    }
}