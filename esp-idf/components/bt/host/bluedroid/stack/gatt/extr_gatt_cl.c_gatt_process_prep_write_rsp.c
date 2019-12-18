#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  value; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ tGATT_VALUE ;
typedef  int /*<<< orphan*/  tGATT_TCB ;
struct TYPE_10__ {scalar_t__ op_subtype; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_INVALID_PDU ; 
 scalar_t__ GATT_PREP_WRITE_RSP_MIN_LEN ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 scalar_t__ GATT_WRITE ; 
 scalar_t__ GATT_WRITE_PREPARE ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_check_write_long_terminate (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_dbg_op_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_send_prepare_write (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void gatt_process_prep_write_rsp (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 op_code,
                                  UINT16 len, UINT8 *p_data)
{
    tGATT_VALUE  value = {0};
    UINT8        *p = p_data;

    GATT_TRACE_DEBUG("value resp op_code = %s len = %d", gatt_dbg_op_name(op_code), len);

    if (len < GATT_PREP_WRITE_RSP_MIN_LEN) {
        GATT_TRACE_ERROR("illegal prepare write response length, discard");
        gatt_end_operation(p_clcb, GATT_INVALID_PDU, &value);
        return;
    }

    STREAM_TO_UINT16 (value.handle, p);
    STREAM_TO_UINT16 (value.offset, p);

    value.len = len - 4;

    memcpy (value.value, p, value.len);

    if (p_clcb->op_subtype == GATT_WRITE_PREPARE) {
        p_clcb->status = GATT_SUCCESS;
        /* application should verify handle offset
           and value are matched or not */

        gatt_end_operation(p_clcb, p_clcb->status, &value);
    } else if (p_clcb->op_subtype == GATT_WRITE ) {
        if (!gatt_check_write_long_terminate(p_tcb, p_clcb, &value)) {
            gatt_send_prepare_write(p_tcb, p_clcb);
        }
    }

}