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
struct TYPE_3__ {int* sub_code; size_t pending_idx; int /*<<< orphan*/ * cur_state; int /*<<< orphan*/ * ref_value; } ;
struct TYPE_4__ {TYPE_1__ op_q; } ;

/* Variables and functions */
 int BTM_BLE_BATCH_SCAN_MAX ; 
 int BTM_BLE_BATCH_SCAN_SUBCODE_MASK ; 
 TYPE_2__ ble_batchscan_cb ; 

void btm_ble_batchscan_deq_op_q(UINT8 *p_opcode, tBTM_BLE_BATCH_SCAN_STATE *cur_state,
                                UINT8 *p_cb_evt, tBTM_BLE_REF_VALUE *p_ref)
{
    *p_cb_evt = (ble_batchscan_cb.op_q.sub_code[ble_batchscan_cb.op_q.pending_idx] >> 4);
    *p_opcode = (ble_batchscan_cb.op_q.sub_code[ble_batchscan_cb.op_q.pending_idx]
                 & BTM_BLE_BATCH_SCAN_SUBCODE_MASK);
    *p_ref = ble_batchscan_cb.op_q.ref_value[ble_batchscan_cb.op_q.pending_idx];
    *cur_state = (ble_batchscan_cb.op_q.cur_state[ble_batchscan_cb.op_q.pending_idx]);
    ble_batchscan_cb.op_q.pending_idx = (ble_batchscan_cb.op_q.pending_idx + 1)
                                        % BTM_BLE_BATCH_SCAN_MAX;
}