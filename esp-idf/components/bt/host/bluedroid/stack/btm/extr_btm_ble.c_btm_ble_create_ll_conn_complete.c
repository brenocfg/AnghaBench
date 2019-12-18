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
typedef  scalar_t__ UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_CONN_IDLE ; 
 int /*<<< orphan*/  HCI_ROLE_UNKNOWN ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  btm_ble_set_conn_st (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_update_mode_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void btm_ble_create_ll_conn_complete (UINT8 status)
{
    if (status != HCI_SUCCESS) {
        btm_ble_set_conn_st(BLE_CONN_IDLE);
        btm_ble_update_mode_operation(HCI_ROLE_UNKNOWN, NULL, status);
    }
}