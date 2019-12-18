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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BLE_REF_VALUE ;
typedef  scalar_t__ UINT8 ;
struct TYPE_3__ {scalar_t__* rep_mode; size_t next_idx; int /*<<< orphan*/ ** p_data; scalar_t__* data_len; scalar_t__* num_records; int /*<<< orphan*/ * ref_value; } ;
struct TYPE_4__ {TYPE_1__ main_rep_q; } ;

/* Variables and functions */
 int BTM_BLE_BATCH_REP_MAIN_Q_SIZE ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ ble_batchscan_cb ; 

tBTM_STATUS btm_ble_batchscan_enq_rep_q(UINT8 report_format, tBTM_BLE_REF_VALUE ref_value)
{
    int i = 0;
    for (i = 0; i < BTM_BLE_BATCH_REP_MAIN_Q_SIZE; i++) {
        if (report_format == ble_batchscan_cb.main_rep_q.rep_mode[i]) {
            return BTM_ILLEGAL_VALUE;
        }
    }

    ble_batchscan_cb.main_rep_q.rep_mode[ble_batchscan_cb.main_rep_q.next_idx] = report_format;
    ble_batchscan_cb.main_rep_q.ref_value[ble_batchscan_cb.main_rep_q.next_idx] = ref_value;
    ble_batchscan_cb.main_rep_q.num_records[ble_batchscan_cb.main_rep_q.next_idx] = 0;
    ble_batchscan_cb.main_rep_q.data_len[ble_batchscan_cb.main_rep_q.next_idx] = 0;
    ble_batchscan_cb.main_rep_q.p_data[ble_batchscan_cb.main_rep_q.next_idx] = NULL;
    BTM_TRACE_DEBUG("btm_ble_batchscan_enq_rep_q: index:%d, rep %d, ref %d",
                    ble_batchscan_cb.main_rep_q.next_idx, report_format, ref_value);

    ble_batchscan_cb.main_rep_q.next_idx = (ble_batchscan_cb.main_rep_q.next_idx + 1)
                                           % BTM_BLE_BATCH_REP_MAIN_Q_SIZE;
    return BTM_SUCCESS;
}