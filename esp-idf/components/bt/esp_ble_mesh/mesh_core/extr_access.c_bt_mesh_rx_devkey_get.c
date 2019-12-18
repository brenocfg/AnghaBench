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
struct TYPE_2__ {int /*<<< orphan*/ * dev_key; } ;

/* Variables and functions */
 TYPE_1__ bt_mesh ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_is_provisioner_en () ; 
 int /*<<< orphan*/ * provisioner_dev_key_get (int /*<<< orphan*/ ) ; 

const u8_t *bt_mesh_rx_devkey_get(size_t index, u16_t src)
{
    const u8_t *key = NULL;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioned()) {
        key = bt_mesh.dev_key;
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioner_en()) {
        key = provisioner_dev_key_get(src);
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (index < 1) {
        key = bt_mesh.dev_key;
    } else {
        key = provisioner_dev_key_get(src);
    }
#endif

    return key;
}