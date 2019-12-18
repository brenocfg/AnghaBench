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
typedef  int /*<<< orphan*/  tBTM_BLE_VSC_CB ;
struct TYPE_2__ {int /*<<< orphan*/  cmn_ble_vsc_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 TYPE_1__ btm_cb ; 

extern void BTM_BleGetVendorCapabilities(tBTM_BLE_VSC_CB *p_cmn_vsc_cb)
{
    BTM_TRACE_DEBUG("BTM_BleGetVendorCapabilities");

    if (NULL != p_cmn_vsc_cb) {
        *p_cmn_vsc_cb = btm_cb.cmn_ble_vsc_cb;
    }
}