#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_IRK_ENABLE_LEN ; 
 int BTM_BLE_META_IRK_ENABLE ; 
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_VENDOR_BLE_RPA_VSC ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btm_ble_resolving_list_vsc_op_cmpl ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS btm_ble_vendor_enable_irk_feature(BOOLEAN enable)
{
    UINT8           param[20], *p;
    tBTM_STATUS     st = BTM_MODE_UNSUPPORTED;

    p = param;
    memset(param, 0, 20);

    /* select feature based on control block settings */
    UINT8_TO_STREAM(p, BTM_BLE_META_IRK_ENABLE);
    UINT8_TO_STREAM(p, enable ? 0x01 : 0x00);

    st = BTM_VendorSpecificCommand (HCI_VENDOR_BLE_RPA_VSC, BTM_BLE_IRK_ENABLE_LEN,
                                    param, btm_ble_resolving_list_vsc_op_cmpl);

    return st;
}