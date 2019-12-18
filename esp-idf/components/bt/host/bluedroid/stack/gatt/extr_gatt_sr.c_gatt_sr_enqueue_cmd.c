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
struct TYPE_5__ {scalar_t__ op_code; scalar_t__ trans_id; int /*<<< orphan*/  status; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {scalar_t__ trans_id; TYPE_2__ sr_cmd; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  TYPE_2__ tGATT_SR_CMD ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 scalar_t__ GATT_CMD_WRITE ; 
 scalar_t__ GATT_HANDLE_VALUE_CONF ; 
 int /*<<< orphan*/  GATT_NOT_FOUND ; 
 scalar_t__ GATT_REQ_MTU ; 
 scalar_t__ GATT_SIGN_CMD_WRITE ; 
 scalar_t__ GATT_TRANS_ID_MAX ; 

UINT32 gatt_sr_enqueue_cmd (tGATT_TCB *p_tcb, UINT8 op_code, UINT16 handle)
{
    tGATT_SR_CMD   *p_cmd = &p_tcb->sr_cmd;
    UINT32          trans_id = 0;

    if ( (p_cmd->op_code == 0) ||
            (op_code == GATT_HANDLE_VALUE_CONF)) { /* no pending request */
        if (op_code == GATT_CMD_WRITE ||
                op_code == GATT_SIGN_CMD_WRITE  ||
                op_code == GATT_REQ_MTU ||
                op_code == GATT_HANDLE_VALUE_CONF) {
            trans_id = ++p_tcb->trans_id;
        } else {
            p_cmd->trans_id   = ++p_tcb->trans_id;
            p_cmd->op_code    = op_code;
            p_cmd->handle     = handle;
            p_cmd->status     = GATT_NOT_FOUND;
            p_tcb->trans_id %= GATT_TRANS_ID_MAX;
            trans_id = p_cmd->trans_id;
        }
    }

    return trans_id;
}