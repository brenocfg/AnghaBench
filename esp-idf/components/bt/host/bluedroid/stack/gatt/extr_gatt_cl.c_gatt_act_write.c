#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  value; scalar_t__ len; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ tGATT_VALUE ;
struct TYPE_10__ {scalar_t__ payload_size; } ;
typedef  TYPE_2__ tGATT_TCB ;
struct TYPE_11__ {int op_subtype; int /*<<< orphan*/  clcb_idx; int /*<<< orphan*/  s_handle; scalar_t__ p_attr_buf; TYPE_2__* p_tcb; } ;
typedef  TYPE_3__ tGATT_CLCB ;
typedef  scalar_t__ UINT8 ;

/* Variables and functions */
 scalar_t__ GATT_CMD_STARTED ; 
 scalar_t__ GATT_CMD_WRITE ; 
 scalar_t__ GATT_CONGESTED ; 
 scalar_t__ GATT_HDR_SIZE ; 
 scalar_t__ GATT_INTERNAL_ERROR ; 
 scalar_t__ GATT_REQ_WRITE ; 
 scalar_t__ GATT_SEC_SIGN_DATA ; 
 scalar_t__ GATT_SIGN_CMD_WRITE ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,scalar_t__,...) ; 
#define  GATT_WRITE 130 
#define  GATT_WRITE_NO_RSP 129 
#define  GATT_WRITE_PREPARE 128 
 int /*<<< orphan*/  gatt_end_operation (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_send_prepare_write (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ gatt_send_write_msg (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gatt_act_write (tGATT_CLCB *p_clcb, UINT8 sec_act)
{
    tGATT_TCB           *p_tcb = p_clcb->p_tcb;
    UINT8               rt = GATT_SUCCESS, op_code = 0;
    tGATT_VALUE         *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;

    if (p_attr) {
        switch (p_clcb->op_subtype) {
        case GATT_WRITE_NO_RSP:
            p_clcb->s_handle = p_attr->handle;
            op_code = (sec_act == GATT_SEC_SIGN_DATA) ? GATT_SIGN_CMD_WRITE : GATT_CMD_WRITE;
            rt = gatt_send_write_msg(p_tcb,
                                     p_clcb->clcb_idx,
                                     op_code,
                                     p_attr->handle,
                                     p_attr->len,
                                     0,
                                     p_attr->value);
            break;

        case GATT_WRITE:
            if (p_attr->len <= (p_tcb->payload_size - GATT_HDR_SIZE)) {
                p_clcb->s_handle = p_attr->handle;

                rt = gatt_send_write_msg(p_tcb,
                                         p_clcb->clcb_idx,
                                         GATT_REQ_WRITE,
                                         p_attr->handle,
                                         p_attr->len,
                                         0,
                                         p_attr->value);
            } else { /* prepare write for long attribute */
                gatt_send_prepare_write(p_tcb, p_clcb);
            }
            break;

        case GATT_WRITE_PREPARE:
            gatt_send_prepare_write(p_tcb, p_clcb);
            break;

        default:
            rt = GATT_INTERNAL_ERROR;
            GATT_TRACE_ERROR("Unknown write type: %d", p_clcb->op_subtype);
            break;
        }
    } else {
        rt = GATT_INTERNAL_ERROR;
    }

    if ((rt != GATT_SUCCESS  && rt != GATT_CMD_STARTED && rt != GATT_CONGESTED)
            || (rt != GATT_CMD_STARTED && p_clcb->op_subtype == GATT_WRITE_NO_RSP)) {
        if (rt != GATT_SUCCESS) {
            GATT_TRACE_ERROR("gatt_act_write() failed op_code=0x%x rt=%d", op_code, rt);
        }
        gatt_end_operation(p_clcb, rt, NULL);
    }
}