#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_BLE_REF_VALUE ;
typedef  int /*<<< orphan*/  tBTM_BLE_BATCH_SCAN_STATE ;
typedef  int UINT8 ;
struct TYPE_3__ {int* sub_code; size_t next_idx; int /*<<< orphan*/ * ref_value; int /*<<< orphan*/ * cur_state; } ;
struct TYPE_4__ {TYPE_1__ op_q; } ;

/* Variables and functions */
 int BTM_BLE_BATCH_SCAN_MAX ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ble_batchscan_cb ; 

void btm_ble_batchscan_enq_op_q(UINT8 opcode, tBTM_BLE_BATCH_SCAN_STATE cur_state,
                                UINT8 cb_evt, tBTM_BLE_REF_VALUE ref_value)
{
    ble_batchscan_cb.op_q.sub_code[ble_batchscan_cb.op_q.next_idx] = (opcode | (cb_evt << 4));
    ble_batchscan_cb.op_q.cur_state[ble_batchscan_cb.op_q.next_idx] = cur_state;
    ble_batchscan_cb.op_q.ref_value[ble_batchscan_cb.op_q.next_idx] = ref_value;
    BTM_TRACE_DEBUG("btm_ble_batchscan_enq_op_q: subcode:%d, Cur_state:%d, ref_value:%d",
                    ble_batchscan_cb.op_q.sub_code[ble_batchscan_cb.op_q.next_idx],
                    ble_batchscan_cb.op_q.cur_state[ble_batchscan_cb.op_q.next_idx],
                    ble_batchscan_cb.op_q.ref_value[ble_batchscan_cb.op_q.next_idx]);
    ble_batchscan_cb.op_q.next_idx = (ble_batchscan_cb.op_q.next_idx + 1)
                                     % BTM_BLE_BATCH_SCAN_MAX;
}