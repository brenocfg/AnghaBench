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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {scalar_t__ (* supports_ble_privacy ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_META_CLEAR_IRK_LEN ; 
 int /*<<< orphan*/  BTM_BLE_META_CLEAR_IRK_LIST ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_VENDOR_BLE_RPA_VSC ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_resolving_list_vsc_op_cmpl ; 
 scalar_t__ btsnd_hcic_ble_clear_resolving_list () ; 
 TYPE_1__* controller_get_interface () ; 
 scalar_t__ stub1 () ; 

tBTM_STATUS btm_ble_clear_resolving_list(void)
{
    tBTM_STATUS st = BTM_NO_RESOURCES;

    if (controller_get_interface()->supports_ble_privacy()) {
        if (btsnd_hcic_ble_clear_resolving_list()) {
            st =  BTM_SUCCESS;
        }
    } else {
        UINT8 param[20] = {0};
        UINT8 *p = param;

        UINT8_TO_STREAM(p, BTM_BLE_META_CLEAR_IRK_LIST);
        st = BTM_VendorSpecificCommand (HCI_VENDOR_BLE_RPA_VSC,
                                        BTM_BLE_META_CLEAR_IRK_LEN,
                                        param,
                                        btm_ble_resolving_list_vsc_op_cmpl);
    }

    return st;
}