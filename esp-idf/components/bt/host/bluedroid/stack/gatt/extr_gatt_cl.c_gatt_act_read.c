#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_READ_MULTI ;
struct TYPE_11__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_16__ {TYPE_1__ uu; int /*<<< orphan*/  len; } ;
struct TYPE_13__ {void* offset; int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {TYPE_7__ uuid; int /*<<< orphan*/  e_handle; int /*<<< orphan*/  s_handle; } ;
struct TYPE_14__ {int /*<<< orphan*/  handle; TYPE_7__ read_multi; TYPE_3__ read_blob; TYPE_2__ browse; } ;
typedef  TYPE_4__ tGATT_CL_MSG ;
struct TYPE_15__ {int op_subtype; int /*<<< orphan*/  clcb_idx; int /*<<< orphan*/  s_handle; int /*<<< orphan*/ * p_attr_buf; int /*<<< orphan*/  first_read_blob_after_read; int /*<<< orphan*/  counter; int /*<<< orphan*/  uuid; int /*<<< orphan*/  e_handle; int /*<<< orphan*/ * p_tcb; } ;
typedef  TYPE_5__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  scalar_t__ UINT8 ;
typedef  void* UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATT_CMD_STARTED ; 
 scalar_t__ GATT_INTERNAL_ERROR ; 
#define  GATT_READ_BY_HANDLE 134 
#define  GATT_READ_BY_TYPE 133 
#define  GATT_READ_CHAR_VALUE 132 
#define  GATT_READ_CHAR_VALUE_HDL 131 
#define  GATT_READ_INC_SRV_UUID128 130 
#define  GATT_READ_MULTIPLE 129 
#define  GATT_READ_PARTIAL 128 
 scalar_t__ GATT_REQ_READ ; 
 scalar_t__ GATT_REQ_READ_BLOB ; 
 scalar_t__ GATT_REQ_READ_BY_TYPE ; 
 scalar_t__ GATT_REQ_READ_MULTI ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,int) ; 
 int /*<<< orphan*/  GATT_UUID_CHAR_DECLARE ; 
 int /*<<< orphan*/  LEN_UUID_16 ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ attp_send_cl_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void gatt_act_read (tGATT_CLCB *p_clcb, UINT16 offset)
{
    tGATT_TCB  *p_tcb = p_clcb->p_tcb;
    UINT8   rt = GATT_INTERNAL_ERROR;
    tGATT_CL_MSG  msg;
    UINT8        op_code = 0;

    memset (&msg, 0, sizeof(tGATT_CL_MSG));

    switch (p_clcb->op_subtype) {
    case GATT_READ_CHAR_VALUE:
    case GATT_READ_BY_TYPE:
        op_code = GATT_REQ_READ_BY_TYPE;
        msg.browse.s_handle = p_clcb->s_handle;
        msg.browse.e_handle = p_clcb->e_handle;
        if (p_clcb->op_subtype == GATT_READ_BY_TYPE) {
            memcpy(&msg.browse.uuid, &p_clcb->uuid, sizeof(tBT_UUID));
        } else {
            msg.browse.uuid.len = LEN_UUID_16;
            msg.browse.uuid.uu.uuid16 = GATT_UUID_CHAR_DECLARE;
        }
        break;

    case GATT_READ_CHAR_VALUE_HDL:
    case GATT_READ_BY_HANDLE:
        if (!p_clcb->counter) {
            op_code = GATT_REQ_READ;
            msg.handle = p_clcb->s_handle;
        } else {
            if (!p_clcb->first_read_blob_after_read) {
                p_clcb->first_read_blob_after_read = TRUE;
            } else {
                p_clcb->first_read_blob_after_read = FALSE;
            }

            GATT_TRACE_DEBUG("gatt_act_read first_read_blob_after_read=%d",
                             p_clcb->first_read_blob_after_read);
            op_code = GATT_REQ_READ_BLOB;
            msg.read_blob.offset = offset;
            msg.read_blob.handle = p_clcb->s_handle;
        }
        p_clcb->op_subtype &= ~ 0x80;
        break;

    case GATT_READ_PARTIAL:
        op_code = GATT_REQ_READ_BLOB;
        msg.read_blob.handle = p_clcb->s_handle;
        msg.read_blob.offset = offset;
        break;

    case GATT_READ_MULTIPLE:
        op_code = GATT_REQ_READ_MULTI;
        memcpy (&msg.read_multi, p_clcb->p_attr_buf, sizeof(tGATT_READ_MULTI));
        break;

    case GATT_READ_INC_SRV_UUID128:
        op_code = GATT_REQ_READ;
        msg.handle = p_clcb->s_handle;
        p_clcb->op_subtype &= ~ 0x90;
        break;

    default:
        GATT_TRACE_ERROR("Unknown read type: %d", p_clcb->op_subtype);
        break;
    }

    if (op_code != 0) {
        rt = attp_send_cl_msg(p_tcb, p_clcb->clcb_idx, op_code, &msg);
    }

    if ( op_code == 0 || (rt != GATT_SUCCESS && rt != GATT_CMD_STARTED)) {
        gatt_end_operation(p_clcb, rt, NULL);
    }
}