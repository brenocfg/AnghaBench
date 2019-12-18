#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  scan_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  wl_state; TYPE_1__ inq_var; } ;
struct TYPE_6__ {TYPE_2__ ble_ctr_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_DUPLICATE_ENABLE ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_DISABLE ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_MODE_NONE ; 
 int /*<<< orphan*/  BTM_BLE_STOP_SCAN ; 
 int /*<<< orphan*/  BTM_BLE_WL_SCAN ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  SP_ADV_ALL ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btm_update_scanner_filter_policy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_set_scan_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_ble_stop_scan(void)
{
    BTM_TRACE_EVENT ("btm_ble_stop_scan ");

    /* Clear the inquiry callback if set */
    btm_cb.ble_ctr_cb.inq_var.scan_type = BTM_BLE_SCAN_MODE_NONE;
    btm_cb.ble_ctr_cb.inq_var.state = BTM_BLE_STOP_SCAN;
    /* stop discovery now */
    btsnd_hcic_ble_set_scan_enable (BTM_BLE_SCAN_DISABLE, BTM_BLE_DUPLICATE_ENABLE);

    btm_update_scanner_filter_policy(SP_ADV_ALL);

    btm_cb.ble_ctr_cb.wl_state &= ~BTM_BLE_WL_SCAN;
}