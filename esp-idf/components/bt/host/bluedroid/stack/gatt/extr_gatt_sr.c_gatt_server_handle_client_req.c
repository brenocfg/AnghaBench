#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ payload_size; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  GATT_CMD_WRITE 141 
#define  GATT_HANDLE_VALUE_CONF 140 
 int /*<<< orphan*/  GATT_INVALID_PDU ; 
#define  GATT_REQ_EXEC_WRITE 139 
#define  GATT_REQ_FIND_INFO 138 
#define  GATT_REQ_FIND_TYPE_VALUE 137 
#define  GATT_REQ_MTU 136 
#define  GATT_REQ_PREPARE_WRITE 135 
#define  GATT_REQ_READ 134 
#define  GATT_REQ_READ_BLOB 133 
#define  GATT_REQ_READ_BY_GRP_TYPE 132 
#define  GATT_REQ_READ_BY_TYPE 131 
#define  GATT_REQ_READ_MULTI 130 
#define  GATT_REQ_WRITE 129 
#define  GATT_SIGN_CMD_WRITE 128 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gatt_process_exec_write_req (TYPE_1__*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  gatt_process_read_multi_req (TYPE_1__*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  gatt_send_error_rsp (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_sr_cmd_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  gatts_process_attribute_req (TYPE_1__*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  gatts_process_find_info (TYPE_1__*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  gatts_process_mtu_req (TYPE_1__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  gatts_process_primary_service_req (TYPE_1__*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  gatts_process_read_by_type_req (TYPE_1__*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  gatts_process_value_conf (TYPE_1__*,int) ; 

void gatt_server_handle_client_req (tGATT_TCB *p_tcb, UINT8 op_code,
                                    UINT16 len, UINT8 *p_data)
{
    /* there is pending command, discard this one */
    if (!gatt_sr_cmd_empty(p_tcb) && op_code != GATT_HANDLE_VALUE_CONF) {
        return;
    }

    /* the size of the message may not be bigger than the local max PDU size*/
    /* The message has to be smaller than the agreed MTU, len does not include op code */
    if (len >= p_tcb->payload_size) {
        GATT_TRACE_ERROR("server receive invalid PDU size:%d pdu size:%d", len + 1, p_tcb->payload_size );
        /* for invalid request expecting response, send it now */
        if (op_code != GATT_CMD_WRITE &&
                op_code != GATT_SIGN_CMD_WRITE &&
                op_code != GATT_HANDLE_VALUE_CONF) {
            gatt_send_error_rsp (p_tcb, GATT_INVALID_PDU, op_code, 0, FALSE);
        }
        /* otherwise, ignore the pkt */
    } else {
        switch (op_code) {
        case GATT_REQ_READ_BY_GRP_TYPE:         /* discover primary services */
        case GATT_REQ_FIND_TYPE_VALUE:          /* discover service by UUID */
            gatts_process_primary_service_req (p_tcb, op_code, len, p_data);
            break;

        case GATT_REQ_FIND_INFO:                /* discover char descrptor */
            gatts_process_find_info(p_tcb, op_code, len, p_data);
            break;

        case GATT_REQ_READ_BY_TYPE:             /* read characteristic value, char descriptor value */
            /* discover characteristic, discover char by UUID */
            gatts_process_read_by_type_req(p_tcb, op_code, len, p_data);
            break;


        case GATT_REQ_READ:                     /* read char/char descriptor value */
        case GATT_REQ_READ_BLOB:
        case GATT_REQ_WRITE:                    /* write char/char descriptor value */
        case GATT_CMD_WRITE:
        case GATT_SIGN_CMD_WRITE:
        case GATT_REQ_PREPARE_WRITE:
            gatts_process_attribute_req (p_tcb, op_code, len, p_data);
            break;

        case GATT_HANDLE_VALUE_CONF:
            gatts_process_value_conf (p_tcb, op_code);
            break;

        case GATT_REQ_MTU:
            gatts_process_mtu_req (p_tcb, len, p_data);
            break;

        case GATT_REQ_EXEC_WRITE:
            gatt_process_exec_write_req (p_tcb, op_code, len, p_data);
            break;

        case GATT_REQ_READ_MULTI:
            gatt_process_read_multi_req (p_tcb, op_code, len, p_data);
            break;

        default:
            break;
        }
    }
}