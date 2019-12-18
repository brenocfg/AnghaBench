#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ payload_size; } ;
typedef  TYPE_1__ tGATT_TCB ;
struct TYPE_25__ {int /*<<< orphan*/  status; scalar_t__ retry_count; int /*<<< orphan*/  rsp_timer_ent; } ;
typedef  TYPE_2__ tGATT_CLCB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_ERROR ; 
#define  GATT_HANDLE_VALUE_IND 141 
#define  GATT_HANDLE_VALUE_NOTIF 140 
#define  GATT_RSP_ERROR 139 
#define  GATT_RSP_EXEC_WRITE 138 
#define  GATT_RSP_FIND_INFO 137 
#define  GATT_RSP_FIND_TYPE_VALUE 136 
#define  GATT_RSP_MTU 135 
#define  GATT_RSP_PREPARE_WRITE 134 
#define  GATT_RSP_READ 133 
#define  GATT_RSP_READ_BLOB 132 
#define  GATT_RSP_READ_BY_GRP_TYPE 131 
#define  GATT_RSP_READ_BY_TYPE 130 
#define  GATT_RSP_READ_MULTI 129 
#define  GATT_RSP_WRITE 128 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  GATT_TRACE_WARNING (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_cl_send_next_cmd_inq (TYPE_1__*) ; 
 TYPE_2__* gatt_cmd_dequeue (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ gatt_cmd_to_rsp_code (scalar_t__) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_process_error_rsp (TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_process_find_type_value_rsp (TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_process_handle_rsp (TYPE_2__*) ; 
 int /*<<< orphan*/  gatt_process_mtu_rsp (TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_process_notification (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_process_prep_write_rsp (TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_process_read_by_type_rsp (TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_process_read_info_rsp (TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gatt_process_read_rsp (TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__*) ; 

void gatt_client_handle_server_rsp (tGATT_TCB *p_tcb, UINT8 op_code,
                                    UINT16 len, UINT8 *p_data)
{
    tGATT_CLCB   *p_clcb = NULL;
    UINT8        rsp_code;

    if (op_code != GATT_HANDLE_VALUE_IND && op_code != GATT_HANDLE_VALUE_NOTIF) {
        p_clcb = gatt_cmd_dequeue(p_tcb, &rsp_code);

        rsp_code = gatt_cmd_to_rsp_code(rsp_code);

        if (p_clcb == NULL || (rsp_code != op_code && op_code != GATT_RSP_ERROR)) {
            GATT_TRACE_WARNING ("ATT - Ignore wrong response. Receives (%02x) \
                                Request(%02x) Ignored", op_code, rsp_code);

            return;
        } else {
            btu_stop_timer (&p_clcb->rsp_timer_ent);
            p_clcb->retry_count = 0;
        }
    }
    /* the size of the message may not be bigger than the local max PDU size*/
    /* The message has to be smaller than the agreed MTU, len does not count op_code */
    if (len >= p_tcb->payload_size) {
        GATT_TRACE_ERROR("invalid response/indicate pkt size: %d, PDU size: %d", len + 1, p_tcb->payload_size);
        if (op_code != GATT_HANDLE_VALUE_NOTIF &&
                op_code != GATT_HANDLE_VALUE_IND) {
            gatt_end_operation(p_clcb, GATT_ERROR, NULL);
        }
    } else {
        switch (op_code) {
        case GATT_RSP_ERROR:
            gatt_process_error_rsp(p_tcb, p_clcb, op_code, len, p_data);
            break;

        case GATT_RSP_MTU:       /* 2 bytes mtu */
            gatt_process_mtu_rsp(p_tcb, p_clcb, len , p_data);
            break;

        case GATT_RSP_FIND_INFO:
            gatt_process_read_info_rsp(p_tcb, p_clcb, op_code, len, p_data);
            break;

        case GATT_RSP_READ_BY_TYPE:
        case GATT_RSP_READ_BY_GRP_TYPE:
            gatt_process_read_by_type_rsp(p_tcb, p_clcb, op_code, len, p_data);
            break;

        case GATT_RSP_READ:
        case GATT_RSP_READ_BLOB:
        case GATT_RSP_READ_MULTI:
            gatt_process_read_rsp(p_tcb, p_clcb, op_code, len, p_data);
            break;

        case GATT_RSP_FIND_TYPE_VALUE: /* disc service with UUID */
            gatt_process_find_type_value_rsp(p_tcb, p_clcb, len, p_data);
            break;

        case GATT_RSP_WRITE:
            gatt_process_handle_rsp(p_clcb);
            break;

        case GATT_RSP_PREPARE_WRITE:
            gatt_process_prep_write_rsp(p_tcb, p_clcb, op_code, len, p_data);
            break;

        case GATT_RSP_EXEC_WRITE:
            gatt_end_operation(p_clcb, p_clcb->status, NULL);
            break;

        case GATT_HANDLE_VALUE_NOTIF:
        case GATT_HANDLE_VALUE_IND:
            gatt_process_notification(p_tcb, op_code, len, p_data);
            break;

        default:
            GATT_TRACE_ERROR("Unknown opcode = %d", op_code);
            break;
        }
    }

    if (op_code != GATT_HANDLE_VALUE_IND && op_code != GATT_HANDLE_VALUE_NOTIF) {
        gatt_cl_send_next_cmd_inq(p_tcb);
    }

    return;
}