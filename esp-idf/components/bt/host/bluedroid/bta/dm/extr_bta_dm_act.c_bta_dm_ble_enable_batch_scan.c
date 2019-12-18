#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_7__ {scalar_t__ tot_scan_results_strg; } ;
typedef  TYPE_2__ tBTM_BLE_VSC_CB ;
struct TYPE_6__ {int /*<<< orphan*/  ref_value; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  discard_rule; int /*<<< orphan*/  scan_window; int /*<<< orphan*/  scan_int; int /*<<< orphan*/  scan_mode; } ;
struct TYPE_8__ {TYPE_1__ ble_enable_scan; } ;
typedef  TYPE_3__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_BATCH_SCAN_ENABLE_EVT ; 
 scalar_t__ BTM_BleEnableBatchScan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_2__*) ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  bta_ble_scan_setup_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void bta_dm_ble_enable_batch_scan (tBTA_DM_MSG *p_data)
{
    tBTM_STATUS btm_status = 0;
    tBTM_BLE_VSC_CB cmn_ble_vsc_cb;

    BTM_BleGetVendorCapabilities(&cmn_ble_vsc_cb);

    if (0 != cmn_ble_vsc_cb.tot_scan_results_strg) {
        btm_status = BTM_BleEnableBatchScan(p_data->ble_enable_scan.scan_mode,
                                            p_data->ble_enable_scan.scan_int,
                                            p_data->ble_enable_scan.scan_window,
                                            p_data->ble_enable_scan.discard_rule,
                                            p_data->ble_enable_scan.addr_type,
                                            p_data->ble_enable_scan.ref_value);
    }

    if (BTM_CMD_STARTED != btm_status) {
        bta_ble_scan_setup_cb(BTM_BLE_BATCH_SCAN_ENABLE_EVT, p_data->ble_enable_scan.ref_value,
                              btm_status);
    }
}