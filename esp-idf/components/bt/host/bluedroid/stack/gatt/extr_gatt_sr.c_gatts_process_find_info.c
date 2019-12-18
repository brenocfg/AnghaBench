#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int payload_size; } ;
typedef  TYPE_1__ tGATT_TCB ;
struct TYPE_16__ {scalar_t__ s_hdl; scalar_t__ e_hdl; scalar_t__ in_use; } ;
typedef  TYPE_2__ tGATT_SR_REG ;
struct TYPE_17__ {TYPE_4__* p_first; } ;
typedef  TYPE_3__ tGATT_SRV_LIST_INFO ;
struct TYPE_18__ {struct TYPE_18__* p_next; int /*<<< orphan*/  i_sreg; } ;
typedef  TYPE_4__ tGATT_SRV_LIST_ELEM ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_20__ {TYPE_3__ srv_list_info; } ;
struct TYPE_19__ {int len; int offset; } ;
typedef  TYPE_5__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* GATT_GET_SR_REG_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ GATT_INVALID_PDU ; 
 scalar_t__ GATT_NOT_FOUND ; 
 scalar_t__ GATT_NO_RESOURCES ; 
 scalar_t__ GATT_SUCCESS ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  attp_send_sr_msg (TYPE_1__*,TYPE_5__*) ; 
 scalar_t__ gatt_build_find_info_rsp (TYPE_2__*,TYPE_5__*,scalar_t__*,scalar_t__,scalar_t__) ; 
 TYPE_9__ gatt_cb ; 
 int /*<<< orphan*/  gatt_send_error_rsp (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gatts_validate_packet_format (scalar_t__,scalar_t__*,scalar_t__**,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ osi_calloc (scalar_t__) ; 
 int /*<<< orphan*/  osi_free (TYPE_5__*) ; 

__attribute__((used)) static void gatts_process_find_info(tGATT_TCB *p_tcb, UINT8 op_code, UINT16 len, UINT8 *p_data)
{
    UINT8           reason = GATT_INVALID_PDU, *p;
    UINT16          s_hdl = 0, e_hdl = 0, buf_len;
    BT_HDR          *p_msg = NULL;
    tGATT_SR_REG    *p_rcb;
    tGATT_SRV_LIST_INFO *p_list = &gatt_cb.srv_list_info;
    tGATT_SRV_LIST_ELEM  *p_srv = NULL;

    reason = gatts_validate_packet_format(op_code, &len, &p_data, NULL, &s_hdl, &e_hdl);

    if (reason == GATT_SUCCESS) {
        buf_len = (UINT16)(sizeof(BT_HDR) + p_tcb->payload_size + L2CAP_MIN_OFFSET);

        if ((p_msg =  (BT_HDR *)osi_calloc(buf_len)) == NULL) {
            reason = GATT_NO_RESOURCES;
        } else {
            reason = GATT_NOT_FOUND;

            p = (UINT8 *)(p_msg + 1) + L2CAP_MIN_OFFSET;
            *p ++ = op_code + 1;
            p_msg->len = 2;

            buf_len = p_tcb->payload_size - 2;

            p_srv = p_list->p_first;

            while (p_srv) {
                p_rcb = GATT_GET_SR_REG_PTR(p_srv->i_sreg);

                if (p_rcb->in_use &&
                        !(p_rcb->s_hdl > e_hdl ||
                          p_rcb->e_hdl < s_hdl)) {
                    reason = gatt_build_find_info_rsp(p_rcb, p_msg, &buf_len, s_hdl, e_hdl);
                    if (reason == GATT_NO_RESOURCES) {
                        reason = GATT_SUCCESS;
                        break;
                    }
                }
                p_srv = p_srv->p_next;
            }
            *p = (UINT8)p_msg->offset;

            p_msg->offset = L2CAP_MIN_OFFSET;
        }
    }

    if (reason != GATT_SUCCESS) {
        if (p_msg) {
            osi_free(p_msg);
        }
        gatt_send_error_rsp (p_tcb, reason, op_code, s_hdl, FALSE);
    } else {
        attp_send_sr_msg(p_tcb, p_msg);
    }

}