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
struct TYPE_2__ {int /*<<< orphan*/  p_app_keys; int /*<<< orphan*/  app_keys; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__ bt_mesh ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_is_provisioner_en () ; 

size_t bt_mesh_rx_appkey_size(void)
{
    size_t size = 0;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioned()) {
        size = ARRAY_SIZE(bt_mesh.app_keys);
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioner_en()) {
        size = ARRAY_SIZE(bt_mesh.p_app_keys);
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    size = ARRAY_SIZE(bt_mesh.app_keys);
    if (bt_mesh_is_provisioner_en()) {
        size += ARRAY_SIZE(bt_mesh.p_app_keys);
    }
#endif

    return size;
}