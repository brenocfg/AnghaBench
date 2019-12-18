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
typedef  scalar_t__ u8_t ;
typedef  void* u16_t ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int passive; void* window; void* itvl; scalar_t__ filter_duplicates; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_HS_FOREVER ; 
 int /*<<< orphan*/  BLE_MESH_DEV_ACTIVE_SCAN ; 
 scalar_t__ BLE_MESH_SCAN_ACTIVE ; 
 scalar_t__ BLE_MESH_SCAN_PASSIVE ; 
 int /*<<< orphan*/  BLE_OWN_ADDR_PUBLIC ; 
 int /*<<< orphan*/  ble_gap_disc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_mesh_atomic_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_atomic_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ bt_mesh_dev ; 
 int /*<<< orphan*/  disc_cb ; 
 TYPE_1__ scan_param ; 

__attribute__((used)) static int start_le_scan(u8_t scan_type, u16_t interval, u16_t window, u8_t filter_dup)
{

    scan_param.filter_duplicates = filter_dup;
    scan_param.itvl = interval;
    scan_param.window = window;

    if (scan_type == BLE_MESH_SCAN_PASSIVE) {
        scan_param.passive = 1;
    } else {
        scan_param.passive = 0;
    }
    ble_gap_disc(BLE_OWN_ADDR_PUBLIC, BLE_HS_FOREVER, &scan_param, disc_cb, NULL);

#if BLE_MESH_DEV
    if (scan_type == BLE_MESH_SCAN_ACTIVE) {
        bt_mesh_atomic_set_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ACTIVE_SCAN);
    } else {
        bt_mesh_atomic_clear_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ACTIVE_SCAN);
    }
#endif

    return 0;
}