#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BLE_REF_VALUE ;
typedef  int /*<<< orphan*/  tBTM_BLE_BATCH_SCAN_MODE ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  cur_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_BATCH_SCAN_READ_REPTS_EVT ; 
 int /*<<< orphan*/  BTM_BLE_BATCH_SCAN_READ_RESULTS ; 
 int BTM_BLE_BATCH_SCAN_READ_RESULTS_LEN ; 
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_ILLEGAL_VALUE ; 
 scalar_t__ BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,scalar_t__) ; 
 scalar_t__ BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BLE_BATCH_SCAN_OCF ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ ble_batchscan_cb ; 
 int /*<<< orphan*/  btm_ble_batchscan_enq_op_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_batchscan_vsc_cmpl_cback ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS btm_ble_read_batchscan_reports(tBTM_BLE_BATCH_SCAN_MODE scan_mode,
        tBTM_BLE_REF_VALUE ref_value)
{
    tBTM_STATUS     status = BTM_NO_RESOURCES;
    UINT8 param[BTM_BLE_BATCH_SCAN_READ_RESULTS_LEN], *pp;
    pp = param;

    memset(param, 0, BTM_BLE_BATCH_SCAN_READ_RESULTS_LEN);

    UINT8_TO_STREAM (pp, BTM_BLE_BATCH_SCAN_READ_RESULTS);
    UINT8_TO_STREAM (pp, scan_mode);

    if ((status = BTM_VendorSpecificCommand (HCI_BLE_BATCH_SCAN_OCF,
                  BTM_BLE_BATCH_SCAN_READ_RESULTS_LEN, param, btm_ble_batchscan_vsc_cmpl_cback))
            != BTM_CMD_STARTED) {
        BTM_TRACE_ERROR("btm_ble_read_batchscan_reports %d", status);
        return BTM_ILLEGAL_VALUE;
    }

    if (BTM_CMD_STARTED == status) {
        /* The user needs to be provided scan read reports event */
        btm_ble_batchscan_enq_op_q(BTM_BLE_BATCH_SCAN_READ_RESULTS, ble_batchscan_cb.cur_state,
                                   BTM_BLE_BATCH_SCAN_READ_REPTS_EVT, ref_value);
    }

    return status;
}