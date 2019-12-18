#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
struct TYPE_11__ {scalar_t__ handle; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ tGATT_DISC_RES ;
struct TYPE_12__ {scalar_t__ operation; scalar_t__ op_subtype; scalar_t__ s_handle; int /*<<< orphan*/  conn_id; TYPE_2__* p_reg; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_4__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_9__ {int /*<<< orphan*/  (* p_disc_res_cb ) (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ;} ;
struct TYPE_10__ {TYPE_1__ app_cb; } ;

/* Variables and functions */
 scalar_t__ GATTC_OPTYPE_DISCOVERY ; 
 scalar_t__ GATT_DISC_CHAR_DSCPT ; 
 scalar_t__ GATT_INFO_RSP_MIN_LEN ; 
 scalar_t__ GATT_INFO_TYPE_PAIR_128 ; 
 scalar_t__ GATT_INFO_TYPE_PAIR_16 ; 
 int /*<<< orphan*/  GATT_INVALID_PDU ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 scalar_t__ LEN_UUID_128 ; 
 scalar_t__ LEN_UUID_16 ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  UNUSED (scalar_t__) ; 
 int /*<<< orphan*/  gatt_act_discovery (TYPE_4__*) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_parse_uuid_from_cmd (int /*<<< orphan*/ *,scalar_t__,scalar_t__**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 

void gatt_process_read_info_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 op_code,
                                UINT16 len, UINT8 *p_data)
{
    tGATT_DISC_RES  result;
    UINT8   *p = p_data, uuid_len = 0, type;

    UNUSED(p_tcb);
    UNUSED(op_code);

    if (len < GATT_INFO_RSP_MIN_LEN) {
        GATT_TRACE_ERROR("invalid Info Response PDU received, discard.");
        gatt_end_operation(p_clcb, GATT_INVALID_PDU, NULL);
        return;
    }
    /* unexpected response */
    if (p_clcb->operation != GATTC_OPTYPE_DISCOVERY || p_clcb->op_subtype != GATT_DISC_CHAR_DSCPT) {
        return;
    }

    STREAM_TO_UINT8(type, p);
    len -= 1;

    if (type == GATT_INFO_TYPE_PAIR_16) {
        uuid_len = LEN_UUID_16;
    } else if (type == GATT_INFO_TYPE_PAIR_128) {
        uuid_len = LEN_UUID_128;
    }

    while (len >= uuid_len + 2) {
        STREAM_TO_UINT16 (result.handle, p);

        if (uuid_len > 0) {
            if (!gatt_parse_uuid_from_cmd(&result.type, uuid_len, &p)) {
                break;
            }
        } else {
            memcpy (&result.type, &p_clcb->uuid, sizeof(tBT_UUID));
        }

        len -= (uuid_len + 2);

        if (p_clcb->p_reg->app_cb.p_disc_res_cb) {
            (*p_clcb->p_reg->app_cb.p_disc_res_cb)(p_clcb->conn_id, p_clcb->op_subtype, &result);
        }
    }

    p_clcb->s_handle = (result.handle == 0) ? 0 : (result.handle + 1);
    /* initiate another request */
    gatt_act_discovery(p_clcb) ;
}