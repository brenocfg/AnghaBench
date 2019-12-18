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
struct TYPE_5__ {scalar_t__ pending_cl_req; scalar_t__ next_slot_inq; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  scalar_t__ tGATT_STATUS ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_AUTH_SIGN_MASK ; 
 scalar_t__ GATT_CMD_STARTED ; 
 int /*<<< orphan*/  GATT_CMD_WRITE ; 
 scalar_t__ GATT_CONGESTED ; 
 scalar_t__ GATT_ERROR ; 
 int /*<<< orphan*/  GATT_HANDLE_VALUE_CONF ; 
 scalar_t__ GATT_INTERNAL_ERROR ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ attp_send_msg_to_l2cap (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_cmd_enq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_start_rsp_timer (int /*<<< orphan*/ ) ; 

tGATT_STATUS attp_cl_send_cmd(tGATT_TCB *p_tcb, UINT16 clcb_idx, UINT8 cmd_code, BT_HDR *p_cmd)
{
    tGATT_STATUS att_ret = GATT_SUCCESS;

    if (p_tcb != NULL) {
        cmd_code &= ~GATT_AUTH_SIGN_MASK;

        /* no pending request or value confirmation */
        if (p_tcb->pending_cl_req == p_tcb->next_slot_inq ||
                cmd_code == GATT_HANDLE_VALUE_CONF) {
            att_ret = attp_send_msg_to_l2cap(p_tcb, p_cmd);
            if (att_ret == GATT_CONGESTED || att_ret == GATT_SUCCESS) {
                /* do not enq cmd if handle value confirmation or set request */
                if (cmd_code != GATT_HANDLE_VALUE_CONF && cmd_code != GATT_CMD_WRITE) {
                    gatt_start_rsp_timer (clcb_idx);
                    gatt_cmd_enq(p_tcb, clcb_idx, FALSE, cmd_code, NULL);
                }
            } else {
                att_ret = GATT_INTERNAL_ERROR;
            }
        } else {
            att_ret = GATT_CMD_STARTED;
            gatt_cmd_enq(p_tcb, clcb_idx, TRUE, cmd_code, p_cmd);
        }
    } else {
        att_ret = GATT_ERROR;
    }

    return att_ret;
}