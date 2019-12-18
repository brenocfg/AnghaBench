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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {scalar_t__ max_filter; } ;

/* Variables and functions */
 scalar_t__ BTM_BLE_MAX_FILTER_COUNTER ; 
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_1__*) ; 
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 TYPE_1__ cmn_ble_adv_vsc_cb ; 

tBTM_STATUS btm_ble_obtain_vsc_details(void)
{
    tBTM_STATUS st = BTM_SUCCESS;

#if BLE_VND_INCLUDED == TRUE
    BTM_BleGetVendorCapabilities(&cmn_ble_adv_vsc_cb);
    if (0 == cmn_ble_adv_vsc_cb.max_filter) {
        st = BTM_MODE_UNSUPPORTED;
        return st;
    }
#else
    cmn_ble_adv_vsc_cb.max_filter = BTM_BLE_MAX_FILTER_COUNTER;
#endif
    return st;
}