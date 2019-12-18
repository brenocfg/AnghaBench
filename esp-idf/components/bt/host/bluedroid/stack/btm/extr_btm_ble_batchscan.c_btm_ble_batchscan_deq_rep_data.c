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
typedef  scalar_t__ tBTM_BLE_REF_VALUE ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_3__ {scalar_t__* rep_mode; scalar_t__* num_records; int pending_idx; scalar_t__* ref_value; scalar_t__* data_len; scalar_t__** p_data; } ;
struct TYPE_4__ {TYPE_1__ main_rep_q; } ;

/* Variables and functions */
 int BTM_BLE_BATCH_REP_MAIN_Q_SIZE ; 
 int BTM_BLE_BATCH_SCAN_MAX ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,scalar_t__) ; 
 TYPE_2__ ble_batchscan_cb ; 

void btm_ble_batchscan_deq_rep_data(UINT8 report_format, tBTM_BLE_REF_VALUE *p_ref_value,
                                    UINT8 *p_num_records, UINT8 **p_data, UINT16 *p_data_len)
{
    int index = 0;

    for (index = 0; index < BTM_BLE_BATCH_REP_MAIN_Q_SIZE; index++) {
        if (report_format == ble_batchscan_cb.main_rep_q.rep_mode[index]) {
            break;
        }
    }

    if (BTM_BLE_BATCH_REP_MAIN_Q_SIZE == index) {
        BTM_TRACE_ERROR("btm_ble_batchscan_deq_rep_data: rep_format:%d not found", report_format);
        return;
    }

    *p_num_records = ble_batchscan_cb.main_rep_q.num_records[index];
    *p_ref_value = ble_batchscan_cb.main_rep_q.ref_value[index];
    *p_data = ble_batchscan_cb.main_rep_q.p_data[index];
    *p_data_len = ble_batchscan_cb.main_rep_q.data_len[index];

    ble_batchscan_cb.main_rep_q.p_data[index] = NULL;
    ble_batchscan_cb.main_rep_q.data_len[index] = 0;
    ble_batchscan_cb.main_rep_q.rep_mode[index] = 0;
    ble_batchscan_cb.main_rep_q.ref_value[index] = 0;
    ble_batchscan_cb.main_rep_q.num_records[index] = 0;

    BTM_TRACE_DEBUG("btm_ble_batchscan_deq_rep_data: index:%d, rep %d, num %d, data_len %d",
                    index, report_format, *p_num_records, *p_data_len);

    ble_batchscan_cb.main_rep_q.pending_idx = (ble_batchscan_cb.main_rep_q.pending_idx + 1)
            % BTM_BLE_BATCH_SCAN_MAX;
}