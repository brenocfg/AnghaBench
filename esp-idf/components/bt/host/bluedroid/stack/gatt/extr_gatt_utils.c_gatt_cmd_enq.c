#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t next_slot_inq; size_t pending_cl_req; TYPE_2__* cl_cmd_q; } ;
typedef  TYPE_1__ tGATT_TCB ;
struct TYPE_5__ {int /*<<< orphan*/  clcb_idx; int /*<<< orphan*/ * p_cmd; int /*<<< orphan*/  op_code; int /*<<< orphan*/  to_send; } ;
typedef  TYPE_2__ tGATT_CMD_Q ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 size_t GATT_CL_MAX_LCB ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN gatt_cmd_enq(tGATT_TCB *p_tcb, UINT16 clcb_idx, BOOLEAN to_send, UINT8 op_code, BT_HDR *p_buf)
{
    tGATT_CMD_Q  *p_cmd = &p_tcb->cl_cmd_q[p_tcb->next_slot_inq];

    p_cmd->to_send = to_send; /* waiting to be sent */
    p_cmd->op_code  = op_code;
    p_cmd->p_cmd    = p_buf;
    p_cmd->clcb_idx = clcb_idx;

    if (!to_send) {
        p_tcb->pending_cl_req = p_tcb->next_slot_inq;
    }

    p_tcb->next_slot_inq ++;
    p_tcb->next_slot_inq %= GATT_CL_MAX_LCB;

    return TRUE;
}