#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ num_handles; int* handles; } ;
struct TYPE_20__ {TYPE_1__ multi_req; } ;
struct TYPE_23__ {TYPE_2__ sr_cmd; int /*<<< orphan*/  transport; int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_5__ tGATT_TCB ;
typedef  scalar_t__ tGATT_STATUS ;
struct TYPE_21__ {int handle; int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct TYPE_24__ {TYPE_3__ attr_value; } ;
typedef  TYPE_6__ tGATTS_RSP ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int UINT16 ;
struct TYPE_22__ {int /*<<< orphan*/  gatt_if; int /*<<< orphan*/  p_db; } ;
struct TYPE_18__ {scalar_t__ req_op_code; scalar_t__ err_status; TYPE_4__* sr_reg; scalar_t__ enable_err_rsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATT_BUSY ; 
 scalar_t__ GATT_INVALID_HANDLE ; 
 int /*<<< orphan*/  GATT_MAX_ATTR_LEN ; 
 scalar_t__ GATT_MAX_READ_MULTI_HANDLES ; 
 scalar_t__ GATT_MAX_SR_PROFILES ; 
 scalar_t__ GATT_NO_RESOURCES ; 
 scalar_t__ GATT_PENDING ; 
 scalar_t__ GATT_STACK_RSP ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int,scalar_t__*) ; 
 TYPE_17__ gatt_cb ; 
 int /*<<< orphan*/  gatt_dequeue_sr_cmd (TYPE_5__*) ; 
 int /*<<< orphan*/  gatt_send_error_rsp (TYPE_5__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_sr_enqueue_cmd (TYPE_5__*,scalar_t__,int) ; 
 scalar_t__ gatt_sr_find_i_rcb_by_handle (int) ; 
 int /*<<< orphan*/  gatt_sr_get_sec_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_sr_process_app_rsp (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,TYPE_6__*) ; 
 int /*<<< orphan*/  gatt_sr_reset_cback_cnt (TYPE_5__*) ; 
 scalar_t__ gatts_read_attr_perm_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 scalar_t__ gatts_read_attr_value_by_handle (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osi_free (TYPE_6__*) ; 
 scalar_t__ osi_malloc (int) ; 

void gatt_process_read_multi_req (tGATT_TCB *p_tcb, UINT8 op_code, UINT16 len, UINT8 *p_data)
{
    UINT32          trans_id;
    UINT16          handle = 0, ll = len;
    UINT8           *p = p_data, i_rcb;
    tGATT_STATUS    err = GATT_SUCCESS;
    UINT8           sec_flag, key_size;
    tGATTS_RSP       *p_msg;

    GATT_TRACE_DEBUG("gatt_process_read_multi_req" );
    p_tcb->sr_cmd.multi_req.num_handles = 0;

    gatt_sr_get_sec_info(p_tcb->peer_bda,
                         p_tcb->transport,
                         &sec_flag,
                         &key_size);

#if GATT_CONFORMANCE_TESTING == TRUE
    if (gatt_cb.enable_err_rsp && gatt_cb.req_op_code == op_code) {
        GATT_TRACE_DEBUG("Conformance tst: forced err rspvofr ReadMultiple: error status=%d\n", gatt_cb.err_status);

        STREAM_TO_UINT16(handle, p);

        gatt_send_error_rsp (p_tcb, gatt_cb.err_status, gatt_cb.req_op_code, handle, FALSE);

        return;
    }
#endif

    while (ll >= 2 && p_tcb->sr_cmd.multi_req.num_handles < GATT_MAX_READ_MULTI_HANDLES) {
        STREAM_TO_UINT16(handle, p);

        if ((i_rcb = gatt_sr_find_i_rcb_by_handle(handle)) < GATT_MAX_SR_PROFILES) {
            p_tcb->sr_cmd.multi_req.handles[p_tcb->sr_cmd.multi_req.num_handles++] = handle;

            /* check read permission */
            if ((err = gatts_read_attr_perm_check(   gatt_cb.sr_reg[i_rcb].p_db,
                       FALSE,
                       handle,
                       sec_flag,
                       key_size))
                    != GATT_SUCCESS) {
                GATT_TRACE_DEBUG("read permission denied : 0x%02x", err);
                break;
            }
        } else {
            /* invalid handle */
            err = GATT_INVALID_HANDLE;
            break;
        }
        ll -= 2;
    }

    if (ll != 0) {
        GATT_TRACE_ERROR("max attribute handle reached in ReadMultiple Request.");
    }

    if (p_tcb->sr_cmd.multi_req.num_handles == 0) {
        err = GATT_INVALID_HANDLE;
    }

    if (err == GATT_SUCCESS) {
        if ((trans_id = gatt_sr_enqueue_cmd (p_tcb, op_code, p_tcb->sr_cmd.multi_req.handles[0])) != 0) {
            gatt_sr_reset_cback_cnt(p_tcb); /* read multiple use multi_rsp_q's count*/

            for (ll = 0; ll < p_tcb->sr_cmd.multi_req.num_handles; ll ++) {
                if ((p_msg = (tGATTS_RSP *)osi_malloc(sizeof(tGATTS_RSP))) != NULL) {
                    memset(p_msg, 0, sizeof(tGATTS_RSP))
                    ;
                    handle = p_tcb->sr_cmd.multi_req.handles[ll];
                    i_rcb = gatt_sr_find_i_rcb_by_handle(handle);

                    p_msg->attr_value.handle = handle;
                    err = gatts_read_attr_value_by_handle(p_tcb,
                                                          gatt_cb.sr_reg[i_rcb].p_db,
                                                          op_code,
                                                          handle,
                                                          0,
                                                          p_msg->attr_value.value,
                                                          &p_msg->attr_value.len,
                                                          GATT_MAX_ATTR_LEN,
                                                          sec_flag,
                                                          key_size,
                                                          trans_id);

                    if (err == GATT_SUCCESS || err == GATT_STACK_RSP) {
                        gatt_sr_process_app_rsp(p_tcb, gatt_cb.sr_reg[i_rcb].gatt_if , trans_id, op_code, GATT_SUCCESS, p_msg);
                    }
                    /* either not using or done using the buffer, release it now */
                    osi_free(p_msg);
                } else {
                    err = GATT_NO_RESOURCES;
                    gatt_dequeue_sr_cmd(p_tcb);
                    break;
                }
            }
        } else {
            err = GATT_NO_RESOURCES;
        }
    }
    /* in theroy BUSY is not possible(should already been checked), protected check */
    if (err != GATT_SUCCESS && err != GATT_STACK_RSP && err != GATT_PENDING && err != GATT_BUSY) {
        gatt_send_error_rsp(p_tcb, err, op_code, handle, FALSE);
    }
}