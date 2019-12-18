#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t pending_cl_req; size_t next_slot_inq; TYPE_2__* cl_cmd_q; } ;
typedef  TYPE_1__ tGATT_TCB ;
struct TYPE_6__ {size_t clcb_idx; int /*<<< orphan*/  op_code; } ;
typedef  TYPE_2__ tGATT_CMD_Q ;
typedef  int /*<<< orphan*/  tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/ * clcb; } ;

/* Variables and functions */
 size_t GATT_CL_MAX_LCB ; 
 TYPE_4__ gatt_cb ; 

tGATT_CLCB *gatt_cmd_dequeue(tGATT_TCB *p_tcb, UINT8 *p_op_code)
{
    tGATT_CMD_Q  *p_cmd = &p_tcb->cl_cmd_q[p_tcb->pending_cl_req];
    tGATT_CLCB *p_clcb = NULL;

    if (p_tcb->pending_cl_req != p_tcb->next_slot_inq) {
        p_clcb = &gatt_cb.clcb[p_cmd->clcb_idx];

        *p_op_code = p_cmd->op_code;

        p_tcb->pending_cl_req ++;
        p_tcb->pending_cl_req %= GATT_CL_MAX_LCB;
    }

    return p_clcb;
}