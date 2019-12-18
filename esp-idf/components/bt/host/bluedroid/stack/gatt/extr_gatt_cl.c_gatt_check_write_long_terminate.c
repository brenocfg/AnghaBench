#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ handle; scalar_t__ len; scalar_t__ value; scalar_t__ offset; } ;
typedef  TYPE_1__ tGATT_VALUE ;
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_EXEC_FLAG ;
struct TYPE_7__ {scalar_t__ counter; int /*<<< orphan*/  status; scalar_t__ p_attr_buf; } ;
typedef  TYPE_2__ tGATT_CLCB ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GATT_ERROR ; 
 int /*<<< orphan*/  GATT_PREP_WRITE_CANCEL ; 
 int /*<<< orphan*/  GATT_PREP_WRITE_EXEC ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  gatt_send_queue_write_cancel (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__,scalar_t__,scalar_t__) ; 

BOOLEAN gatt_check_write_long_terminate(tGATT_TCB  *p_tcb, tGATT_CLCB *p_clcb, tGATT_VALUE *p_rsp_value)
{
    tGATT_VALUE         *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;
    BOOLEAN             exec = FALSE;
    tGATT_EXEC_FLAG     flag = GATT_PREP_WRITE_EXEC;

    GATT_TRACE_DEBUG("gatt_check_write_long_terminate ");
    /* check the first write response status */
    if (p_rsp_value != NULL) {
        if (p_rsp_value->handle != p_attr->handle ||
                p_rsp_value->len != p_clcb->counter ||
                memcmp(p_rsp_value->value, p_attr->value + p_attr->offset, p_rsp_value->len)) {
            /* data does not match    */
            p_clcb->status = GATT_ERROR;
            flag = GATT_PREP_WRITE_CANCEL;
            exec = TRUE;
        } else { /* response checking is good */
            p_clcb->status = GATT_SUCCESS;
            /* update write offset and check if end of attribute value */
            if ((p_attr->offset += p_rsp_value->len) >= p_attr->len) {
                exec = TRUE;
            }
        }
    }
    if (exec) {
        gatt_send_queue_write_cancel (p_tcb, p_clcb, flag);
        return TRUE;
    }
    return FALSE;
}