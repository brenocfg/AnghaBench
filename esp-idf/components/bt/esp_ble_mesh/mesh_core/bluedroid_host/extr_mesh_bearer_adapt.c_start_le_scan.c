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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
typedef  int tGATT_IF ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_ADDR_PUBLIC ; 
 int /*<<< orphan*/  BLE_MESH_BTM_CHECK_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLE_MESH_DEV_ACTIVE_SCAN ; 
 int /*<<< orphan*/  BLE_MESH_SCAN_ACTIVE ; 
 int /*<<< orphan*/  BLE_MESH_SP_ADV_ALL ; 
 int /*<<< orphan*/  BTM_BleScan (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTM_BleSetScanFilterParams (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_mesh_atomic_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_atomic_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ bt_mesh_dev ; 
 int /*<<< orphan*/  bt_mesh_scan_results_cb ; 

__attribute__((used)) static int start_le_scan(u8_t scan_type, u16_t interval, u16_t window, u8_t filter_dup)
{
    UINT8 scan_fil_policy = BLE_MESH_SP_ADV_ALL; /* No whitelist for BLE Mesh */
    UINT8 addr_type_own = BLE_MESH_ADDR_PUBLIC;  /* Currently only support Public Address */
    tGATT_IF client_if = 0xFF; /* Default GATT interface id */

    BLE_MESH_BTM_CHECK_STATUS(
        BTM_BleSetScanFilterParams(client_if, interval, window, scan_type, addr_type_own,
                                   filter_dup, scan_fil_policy, NULL));

    /* BLE Mesh scan permanently, so no duration of scan here */
    BLE_MESH_BTM_CHECK_STATUS(BTM_BleScan(true, 0, bt_mesh_scan_results_cb, NULL, NULL));

#if BLE_MESH_DEV
    if (scan_type == BLE_MESH_SCAN_ACTIVE) {
        bt_mesh_atomic_set_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ACTIVE_SCAN);
    } else {
        bt_mesh_atomic_clear_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ACTIVE_SCAN);
    }
#endif

    return 0;
}