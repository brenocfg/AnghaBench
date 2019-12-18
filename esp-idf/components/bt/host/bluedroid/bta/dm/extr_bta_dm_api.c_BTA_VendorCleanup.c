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
struct TYPE_3__ {scalar_t__ max_filter; scalar_t__ tot_scan_results_strg; scalar_t__ adv_inst_max; } ;
typedef  TYPE_1__ tBTM_BLE_VSC_CB ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_1__*) ; 
 int /*<<< orphan*/  btm_ble_adv_filter_cleanup () ; 
 int /*<<< orphan*/  btm_ble_batchscan_cleanup () ; 
 int /*<<< orphan*/  btm_ble_multi_adv_cleanup () ; 
 int /*<<< orphan*/  btm_ble_resolving_list_cleanup () ; 

void BTA_VendorCleanup (void)
{
    tBTM_BLE_VSC_CB cmn_ble_vsc_cb;
    BTM_BleGetVendorCapabilities(&cmn_ble_vsc_cb);

#if (BLE_INCLUDED == TRUE && BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE)
    btm_ble_adv_filter_cleanup();       // when BLE_VND_INCLUDED is false, this function will be ignore, so move it out of "if"

#if 0                                   //by TH, comment out temporarily
    if (cmn_ble_vsc_cb.max_filter > 0) {
        btm_ble_adv_filter_cleanup();
#if BLE_PRIVACY_SPT == TRUE
        btm_ble_resolving_list_cleanup ();
#endif
    }
#endif

    if (cmn_ble_vsc_cb.tot_scan_results_strg > 0) {
        btm_ble_batchscan_cleanup();
    }
#endif

    if (cmn_ble_vsc_cb.adv_inst_max > 0) {
        btm_ble_multi_adv_cleanup();
    }
}