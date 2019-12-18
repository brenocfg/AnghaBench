#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ payload_size; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int /*<<< orphan*/  tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 scalar_t__ GATT_DEF_BLE_MTU_SIZE ; 
 int /*<<< orphan*/  GATT_INVALID_PDU ; 
 scalar_t__ GATT_MTU_RSP_MIN_LEN ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_end_operation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gatt_process_mtu_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT16 len, UINT8 *p_data)
{
    UINT16 mtu;
    tGATT_STATUS    status = GATT_SUCCESS;

    if (len < GATT_MTU_RSP_MIN_LEN) {
        GATT_TRACE_ERROR("invalid MTU response PDU received, discard.");
        status = GATT_INVALID_PDU;
    } else {
        STREAM_TO_UINT16(mtu, p_data);

        if (mtu < p_tcb->payload_size && mtu >= GATT_DEF_BLE_MTU_SIZE) {
            p_tcb->payload_size = mtu;
        }
    }
    /* host will set packet data length to 251 automatically if remote device support set packet data length,
       so l2cble_set_fixed_channel_tx_data_length() is not necessary.
       l2cble_set_fixed_channel_tx_data_length(p_tcb->peer_bda, L2CAP_ATT_CID, p_tcb->payload_size);
    */
    gatt_end_operation(p_clcb, status, NULL);
}