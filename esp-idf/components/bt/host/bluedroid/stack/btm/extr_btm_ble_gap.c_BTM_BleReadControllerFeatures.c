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
typedef  int /*<<< orphan*/  tBTM_BLE_CTRL_FEATURES_CBACK ;
struct TYPE_3__ {scalar_t__ values_read; } ;
struct TYPE_4__ {TYPE_1__ cmn_ble_vsc_cb; } ;

/* Variables and functions */
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 scalar_t__ BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BLE_VENDOR_CAP_OCF ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_ble_vendor_capability_vsc_cmpl_cback ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/ * p_ctrl_le_feature_rd_cmpl_cback ; 

extern void BTM_BleReadControllerFeatures(tBTM_BLE_CTRL_FEATURES_CBACK  *p_vsc_cback)
{
    if (TRUE == btm_cb.cmn_ble_vsc_cb.values_read) {
        return;
    }

#if BLE_VND_INCLUDED == TRUE
    BTM_TRACE_DEBUG("BTM_BleReadControllerFeatures");

    p_ctrl_le_feature_rd_cmpl_cback = p_vsc_cback;
    if ( BTM_VendorSpecificCommand (HCI_BLE_VENDOR_CAP_OCF,
                                    0,
                                    NULL,
                                    btm_ble_vendor_capability_vsc_cmpl_cback)
            != BTM_CMD_STARTED) {
        BTM_TRACE_ERROR("LE Get_Vendor Capabilities Command Failed.");
    }
#else
    UNUSED(p_vsc_cback);
#endif
    return ;
}