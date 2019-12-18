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
typedef  int /*<<< orphan*/  tBTM_BLE_TX_TIME_MS ;
typedef  int /*<<< orphan*/  tBTM_BLE_RX_TIME_MS ;
typedef  int /*<<< orphan*/  tBTM_BLE_IDLE_TIME_MS ;
typedef  int /*<<< orphan*/  tBTM_BLE_ENERGY_USED ;
typedef  scalar_t__ tBTA_STATUS ;
typedef  int /*<<< orphan*/  tBTA_DM_CONTRL_STATE ;
struct TYPE_2__ {int /*<<< orphan*/  (* p_energy_info_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ BTA_FAILURE ; 
 scalar_t__ BTA_SUCCESS ; 
 scalar_t__ BTM_SUCCESS ; 
 TYPE_1__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_pm_obtain_controller_state () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bta_ble_energy_info_cmpl(tBTM_BLE_TX_TIME_MS tx_time,
                                     tBTM_BLE_RX_TIME_MS rx_time,
                                     tBTM_BLE_IDLE_TIME_MS idle_time,
                                     tBTM_BLE_ENERGY_USED  energy_used,
                                     tBTM_STATUS status)
{
    tBTA_STATUS st = (status == BTM_SUCCESS) ? BTA_SUCCESS : BTA_FAILURE;
    tBTA_DM_CONTRL_STATE ctrl_state = 0;
#if ((defined BTA_GATT_INCLUDED) &&  (BTA_GATT_INCLUDED == TRUE) && SDP_INCLUDED == TRUE)
    if (BTA_SUCCESS == st) {
        ctrl_state = bta_dm_pm_obtain_controller_state();
    }
#endif
    if (bta_dm_cb.p_energy_info_cback) {
        bta_dm_cb.p_energy_info_cback(tx_time, rx_time, idle_time, energy_used, ctrl_state, st);
    }
}