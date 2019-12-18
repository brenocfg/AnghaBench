#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  handle; scalar_t__ len; int /*<<< orphan*/  value; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ tGATT_VALUE ;
struct TYPE_12__ {scalar_t__ ind_count; int /*<<< orphan*/  tcb_idx; } ;
typedef  TYPE_3__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_cmpl_cb ) (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {TYPE_1__ app_cb; int /*<<< orphan*/  gatt_if; scalar_t__ in_use; } ;
typedef  TYPE_4__ tGATT_REG ;
typedef  int /*<<< orphan*/  tGATT_CL_COMPLETE ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_14__ {TYPE_4__* cl_rcb; } ;

/* Variables and functions */
 scalar_t__ GATTC_OPTYPE_INDICATION ; 
 scalar_t__ GATTC_OPTYPE_NOTIFICATION ; 
 scalar_t__ GATT_CREATE_CONN_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_HANDLE_IS_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_HANDLE_VALUE_CONF ; 
 scalar_t__ GATT_HANDLE_VALUE_IND ; 
 scalar_t__ GATT_HANDLE_VALUE_NOTIF ; 
 scalar_t__ GATT_MAX_APPS ; 
 scalar_t__ GATT_NOTIFICATION_MIN_LEN ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,...) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  attp_send_cl_msg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_8__ gatt_cb ; 
 int /*<<< orphan*/  gatt_get_link_encrypt_status (TYPE_3__*) ; 
 int /*<<< orphan*/  gatt_start_ind_ack_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gatt_process_notification(tGATT_TCB *p_tcb, UINT8 op_code,
                               UINT16 len, UINT8 *p_data)
{
    tGATT_VALUE     value = {0};
    tGATT_REG       *p_reg;
    UINT16          conn_id;
    tGATT_STATUS    encrypt_status;
    UINT8           *p = p_data, i,
                     event = (op_code == GATT_HANDLE_VALUE_NOTIF) ? GATTC_OPTYPE_NOTIFICATION : GATTC_OPTYPE_INDICATION;

    GATT_TRACE_DEBUG("gatt_process_notification ");

    if (len < GATT_NOTIFICATION_MIN_LEN) {
        GATT_TRACE_ERROR("illegal notification PDU length, discard");
        return;
    }

    STREAM_TO_UINT16 (value.handle, p);
    value.len = len - 2;
    memcpy (value.value, p, value.len);

    if (!GATT_HANDLE_IS_VALID(value.handle)) {
        /* illegal handle, send ack now */
        if (op_code == GATT_HANDLE_VALUE_IND) {
            attp_send_cl_msg(p_tcb, 0, GATT_HANDLE_VALUE_CONF, NULL);
        }
        return;
    }

    if (event == GATTC_OPTYPE_INDICATION) {
        if (p_tcb->ind_count) {
            /* this is an error case that receiving an indication but we
               still has an indication not being acked yet.
               For now, just log the error reset the counter.
               Later we need to disconnect the link unconditionally.
            */
            GATT_TRACE_ERROR("gatt_process_notification rcv Ind. but ind_count=%d (will reset ind_count)",  p_tcb->ind_count);
        }
        p_tcb->ind_count = 0;
    }

    /* should notify all registered client with the handle value notificaion/indication
       Note: need to do the indication count and start timer first then do callback
     */

    for (i = 0, p_reg = gatt_cb.cl_rcb; i < GATT_MAX_APPS; i++, p_reg++) {
        if (p_reg->in_use && p_reg->app_cb.p_cmpl_cb && (event == GATTC_OPTYPE_INDICATION)) {
            p_tcb->ind_count++;
        }
    }

    if (event == GATTC_OPTYPE_INDICATION) {
        /* start a timer for app confirmation */
        if (p_tcb->ind_count > 0) {
            gatt_start_ind_ack_timer(p_tcb);
        } else { /* no app to indicate, or invalid handle */
            attp_send_cl_msg(p_tcb, 0, GATT_HANDLE_VALUE_CONF, NULL);
        }
    }

    encrypt_status = gatt_get_link_encrypt_status(p_tcb);
    for (i = 0, p_reg = gatt_cb.cl_rcb; i < GATT_MAX_APPS; i++, p_reg++) {
        if (p_reg->in_use && p_reg->app_cb.p_cmpl_cb) {
            conn_id = GATT_CREATE_CONN_ID(p_tcb->tcb_idx, p_reg->gatt_if);
            (*p_reg->app_cb.p_cmpl_cb) (conn_id, event, encrypt_status, (tGATT_CL_COMPLETE *)&value);
        }
    }

}