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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_DEV_ADVERTISING ; 
 int /*<<< orphan*/  BLE_MESH_DEV_KEEP_ADVERTISING ; 
 int /*<<< orphan*/  ble_gap_adv_stop () ; 
 int /*<<< orphan*/  bt_mesh_atomic_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_atomic_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ bt_mesh_dev ; 

int bt_le_adv_stop(void)
{
#if BLE_MESH_DEV
    bt_mesh_atomic_clear_bit(bt_mesh_dev.flags, BLE_MESH_DEV_KEEP_ADVERTISING);
    if (!bt_mesh_atomic_test_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ADVERTISING)) {
        return 0;
    }
#endif
    ble_gap_adv_stop();

#if BLE_MESH_DEV
    bt_mesh_atomic_clear_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ADVERTISING);
#endif

    return 0;
}