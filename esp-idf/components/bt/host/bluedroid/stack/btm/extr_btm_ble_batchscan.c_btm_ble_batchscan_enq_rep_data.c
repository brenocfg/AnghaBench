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
typedef  scalar_t__ UINT8 ;
struct TYPE_3__ {scalar_t__* rep_mode; int* data_len; scalar_t__** p_data; scalar_t__* num_records; } ;
struct TYPE_4__ {TYPE_1__ main_rep_q; } ;

/* Variables and functions */
 int BTM_BLE_BATCH_REP_MAIN_Q_SIZE ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_2__ ble_batchscan_cb ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  osi_free (scalar_t__*) ; 
 scalar_t__* osi_malloc (scalar_t__) ; 

void btm_ble_batchscan_enq_rep_data(UINT8 report_format, UINT8 num_records, UINT8 *p_data,
                                    UINT8 data_len)
{
    int index = 0, len = 0;
    UINT8 *p_orig_data = NULL, *p_app_data = NULL;

    for (index = 0; index < BTM_BLE_BATCH_REP_MAIN_Q_SIZE; index++) {
        if (report_format == ble_batchscan_cb.main_rep_q.rep_mode[index]) {
            break;
        }
    }

    BTM_TRACE_DEBUG("btm_ble_batchscan_enq_rep_data: index:%d, rep %d, num %d len : %d",
                    index, report_format, num_records, data_len);

    if (index < BTM_BLE_BATCH_REP_MAIN_Q_SIZE && data_len > 0 && num_records > 0) {
        len = ble_batchscan_cb.main_rep_q.data_len[index];
        p_orig_data = ble_batchscan_cb.main_rep_q.p_data[index];
        if (NULL != p_orig_data) {
            p_app_data = osi_malloc(len + data_len);
            memcpy(p_app_data, p_orig_data, len);
            memcpy(p_app_data + len, p_data, data_len);
            osi_free(p_orig_data);
            ble_batchscan_cb.main_rep_q.p_data[index] = p_app_data;
            ble_batchscan_cb.main_rep_q.num_records[index] += num_records;
            ble_batchscan_cb.main_rep_q.data_len[index] += data_len;
        } else {
            p_app_data = osi_malloc(data_len);
            memcpy(p_app_data, p_data, data_len);
            ble_batchscan_cb.main_rep_q.p_data[index] = p_app_data;
            ble_batchscan_cb.main_rep_q.num_records[index] = num_records;
            ble_batchscan_cb.main_rep_q.data_len[index] = data_len;
        }
    }
}