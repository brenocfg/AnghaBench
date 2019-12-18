#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
struct TYPE_5__ {scalar_t__ p_attr_list; } ;
typedef  TYPE_1__ tGATT_SVC_DB ;
typedef  scalar_t__ tGATT_STATUS ;
typedef  int /*<<< orphan*/  tGATT_SEC_FLAG ;
struct TYPE_6__ {scalar_t__ handle; scalar_t__ p_next; } ;
typedef  TYPE_2__ tGATT_ATTR16 ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ UINT16 ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ GATT_NOT_FOUND ; 
 scalar_t__ GATT_PENDING ; 
 scalar_t__ GATT_REQ_READ_BLOB ; 
 scalar_t__ GATT_STACK_RSP ; 
 scalar_t__ gatts_send_app_read_request (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_attr_value (TYPE_2__*,scalar_t__,scalar_t__**,int,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

tGATT_STATUS gatts_read_attr_value_by_handle(tGATT_TCB *p_tcb,
        tGATT_SVC_DB *p_db,
        UINT8 op_code,
        UINT16 handle, UINT16 offset,
        UINT8 *p_value, UINT16 *p_len,
        UINT16 mtu,
        tGATT_SEC_FLAG sec_flag,
        UINT8 key_size,
        UINT32 trans_id)
{
    tGATT_STATUS status = GATT_NOT_FOUND;
    tGATT_ATTR16  *p_attr;
    UINT8       *pp = p_value;

    if (p_db && p_db->p_attr_list) {
        p_attr = (tGATT_ATTR16 *)p_db->p_attr_list;

        while (p_attr && handle >= p_attr->handle) {
            if (p_attr->handle == handle) {
                status = read_attr_value (p_attr, offset, &pp,
                                          (BOOLEAN)(op_code == GATT_REQ_READ_BLOB),
                                          mtu, p_len, sec_flag, key_size);

                if ((status == GATT_PENDING) || (status == GATT_STACK_RSP)) {
                    BOOLEAN need_rsp = (status != GATT_STACK_RSP);
                    status = gatts_send_app_read_request(p_tcb, op_code, p_attr->handle, offset, trans_id, need_rsp);
                }
                break;
            }
            p_attr = (tGATT_ATTR16 *)p_attr->p_next;
        }
    }


    return status;
}