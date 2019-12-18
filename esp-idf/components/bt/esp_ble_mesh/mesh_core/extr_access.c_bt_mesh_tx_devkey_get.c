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
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_2__ {scalar_t__* dev_key; } ;

/* Variables and functions */
 scalar_t__ FAST_PROV ; 
 scalar_t__ NODE ; 
 scalar_t__ PROVISIONER ; 
 TYPE_1__ bt_mesh ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_is_provisioner_en () ; 
 scalar_t__* fast_prov_dev_key_get (int /*<<< orphan*/ ) ; 
 scalar_t__* provisioner_dev_key_get (int /*<<< orphan*/ ) ; 

const u8_t *bt_mesh_tx_devkey_get(u8_t role, u16_t dst)
{
    const u8_t *key = NULL;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (role == NODE) {
        if (bt_mesh_is_provisioned()) {
            key = bt_mesh.dev_key;
        }
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (role == PROVISIONER) {
        if (bt_mesh_is_provisioner_en()) {
            key = provisioner_dev_key_get(dst);
        }
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (role == NODE) {
        if (bt_mesh_is_provisioned()) {
            key = bt_mesh.dev_key;
        }
    } else if (role == PROVISIONER) {
        if (bt_mesh_is_provisioner_en()) {
            key = provisioner_dev_key_get(dst);
        }
    } else if (role == FAST_PROV) {
#if CONFIG_BLE_MESH_FAST_PROV
        key = fast_prov_dev_key_get(dst);
#endif
    }
#endif

    return key;
}