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
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_EXEC_FLAG ;
typedef  int /*<<< orphan*/  tGATT_CL_MSG ;
struct TYPE_4__ {int /*<<< orphan*/  clcb_idx; } ;
typedef  TYPE_1__ tGATT_CLCB ;
typedef  scalar_t__ UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_REQ_EXEC_WRITE ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 scalar_t__ attp_send_cl_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

void gatt_send_queue_write_cancel (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, tGATT_EXEC_FLAG flag)
{
    UINT8       rt ;

    GATT_TRACE_DEBUG("gatt_send_queue_write_cancel ");

    rt = attp_send_cl_msg(p_tcb, p_clcb->clcb_idx, GATT_REQ_EXEC_WRITE, (tGATT_CL_MSG *)&flag);

    if (rt != GATT_SUCCESS) {
        gatt_end_operation(p_clcb, rt, NULL);
    }
}