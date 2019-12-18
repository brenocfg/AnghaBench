#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ status; int /*<<< orphan*/  handle; int /*<<< orphan*/ * p_rsp_msg; } ;
struct TYPE_12__ {TYPE_2__ sr_cmd; int /*<<< orphan*/  payload_size; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  scalar_t__ tGATT_STATUS ;
typedef  int /*<<< orphan*/  tGATT_SR_MSG ;
typedef  scalar_t__ tGATT_IF ;
typedef  int /*<<< orphan*/  tGATTS_RSP ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATT_REQ_EXEC_WRITE ; 
 scalar_t__ GATT_REQ_PREPARE_WRITE ; 
 scalar_t__ GATT_REQ_READ_MULTI ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 scalar_t__ GATT_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * attp_build_sr_msg (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ attp_send_sr_msg (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_dequeue_sr_cmd (TYPE_1__*) ; 
 scalar_t__ gatt_send_error_rsp (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_sr_is_cback_cnt_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_sr_reset_cback_cnt (TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_sr_update_cback_cnt (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_sr_update_prep_cnt (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_read_multi_rsp (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

tGATT_STATUS gatt_sr_process_app_rsp (tGATT_TCB *p_tcb, tGATT_IF gatt_if,
                                      UINT32 trans_id, UINT8 op_code,
                                      tGATT_STATUS status, tGATTS_RSP *p_msg)
{
    tGATT_STATUS    ret_code = GATT_SUCCESS;
    UNUSED(trans_id);

    GATT_TRACE_DEBUG("gatt_sr_process_app_rsp gatt_if=%d\n", gatt_if);

    gatt_sr_update_cback_cnt(p_tcb, gatt_if, FALSE, FALSE);

    if (op_code == GATT_REQ_READ_MULTI) {
        /* If no error and still waiting, just return */
        if (!process_read_multi_rsp (&p_tcb->sr_cmd, status, p_msg, p_tcb->payload_size)) {
            return (GATT_SUCCESS);
        }
    } else {
        if (op_code == GATT_REQ_PREPARE_WRITE && status == GATT_SUCCESS) {
            gatt_sr_update_prep_cnt(p_tcb, gatt_if, TRUE, FALSE);
        }

        if (op_code == GATT_REQ_EXEC_WRITE && status != GATT_SUCCESS) {
            gatt_sr_reset_cback_cnt(p_tcb);
        }

        p_tcb->sr_cmd.status = status;

        if (gatt_sr_is_cback_cnt_zero(p_tcb)
                && status == GATT_SUCCESS) {
            if (p_tcb->sr_cmd.p_rsp_msg == NULL) {
                p_tcb->sr_cmd.p_rsp_msg = attp_build_sr_msg (p_tcb, (UINT8)(op_code + 1), (tGATT_SR_MSG *)p_msg);
            } else {
                GATT_TRACE_ERROR("Exception!!! already has respond message\n");
            }
        }
    }
    if (gatt_sr_is_cback_cnt_zero(p_tcb)) {
        if ( (p_tcb->sr_cmd.status == GATT_SUCCESS) && (p_tcb->sr_cmd.p_rsp_msg) ) {
            ret_code = attp_send_sr_msg (p_tcb, p_tcb->sr_cmd.p_rsp_msg);
            p_tcb->sr_cmd.p_rsp_msg = NULL;
        } else {
            if (p_tcb->sr_cmd.status == GATT_SUCCESS){
                status = GATT_UNKNOWN_ERROR;
            }
            ret_code = gatt_send_error_rsp (p_tcb, status, op_code, p_tcb->sr_cmd.handle, FALSE);
        }

        gatt_dequeue_sr_cmd(p_tcb);
    }

    GATT_TRACE_DEBUG("gatt_sr_process_app_rsp ret_code=%d\n", ret_code);

    return ret_code;
}