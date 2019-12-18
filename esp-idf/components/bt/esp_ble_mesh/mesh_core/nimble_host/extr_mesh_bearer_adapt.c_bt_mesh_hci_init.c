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
struct TYPE_2__ {int /*<<< orphan*/  hci_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_HCI_VERSION_5_0 ; 
 int /*<<< orphan*/  ble_hs_hci_get_hci_version () ; 
 TYPE_1__ bt_mesh_dev ; 

void bt_mesh_hci_init(void)
{
    /**
     * Currently 20ms non-connectable adv interval is supported, and we need to add
     * a flag to indicate this support.
     */
#ifdef CONFIG_BLE_MESH_HCI_5_0
    bt_mesh_dev.hci_version = BLE_MESH_HCI_VERSION_5_0;
#else
    bt_mesh_dev.hci_version = ble_hs_hci_get_hci_version();
#endif
    return;
}