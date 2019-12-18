#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_4__ {scalar_t__ energy_support; } ;
typedef  TYPE_1__ tBTM_BLE_VSC_CB ;
typedef  int /*<<< orphan*/  tBTM_BLE_ENERGY_INFO_CBACK ;
struct TYPE_5__ {int /*<<< orphan*/ * p_ener_cback; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_1__*) ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BLE_ENERGY_INFO_OCF ; 
 TYPE_2__ ble_energy_info_cb ; 
 int /*<<< orphan*/  btm_ble_cont_energy_cmpl_cback ; 

tBTM_STATUS BTM_BleGetEnergyInfo(tBTM_BLE_ENERGY_INFO_CBACK *p_ener_cback)
{
    tBTM_STATUS status = BTM_ILLEGAL_VALUE;
    tBTM_BLE_VSC_CB cmn_ble_vsc_cb;

    BTM_BleGetVendorCapabilities(&cmn_ble_vsc_cb);

    BTM_TRACE_EVENT("BTM_BleGetEnergyInfo\n");

    if (0 == cmn_ble_vsc_cb.energy_support) {
        BTM_TRACE_ERROR("Controller does not support get energy info\n");
        return BTM_ERR_PROCESSING;
    }

    ble_energy_info_cb.p_ener_cback = p_ener_cback;
    if ((status = BTM_VendorSpecificCommand (HCI_BLE_ENERGY_INFO_OCF, 0, NULL,
                  btm_ble_cont_energy_cmpl_cback)) != BTM_CMD_STARTED) {
        BTM_TRACE_ERROR("BTM_BleGetEnergyInfo status: %d", status);
        return BTM_ILLEGAL_VALUE;
    }

    return status;
}