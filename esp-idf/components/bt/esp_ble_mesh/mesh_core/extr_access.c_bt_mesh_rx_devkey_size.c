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

/* Variables and functions */
 scalar_t__ bt_mesh_is_provisioner_en () ; 

size_t bt_mesh_rx_devkey_size(void)
{
    size_t size = 0;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (!bt_mesh_is_provisioner_en()) {
        size = 1;
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioner_en()) {
        size = 1;
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    size = 1;
    if (bt_mesh_is_provisioner_en()) {
        size += 1;
    }
#endif

    return size;
}