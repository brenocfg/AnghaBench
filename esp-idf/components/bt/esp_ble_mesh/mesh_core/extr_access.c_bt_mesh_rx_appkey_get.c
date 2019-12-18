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
struct bt_mesh_app_key {int dummy; } ;
struct TYPE_2__ {struct bt_mesh_app_key* app_keys; struct bt_mesh_app_key** p_app_keys; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct bt_mesh_app_key*) ; 
 TYPE_1__ bt_mesh ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_is_provisioner_en () ; 

struct bt_mesh_app_key *bt_mesh_rx_appkey_get(size_t index)
{
    struct bt_mesh_app_key *key = NULL;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioned()) {
        key = &bt_mesh.app_keys[index];
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioner_en()) {
        key = bt_mesh.p_app_keys[index];
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (index < ARRAY_SIZE(bt_mesh.app_keys)) {
        key = &bt_mesh.app_keys[index];
    } else {
        key = bt_mesh.p_app_keys[index - ARRAY_SIZE(bt_mesh.app_keys)];
    }
#endif

    return key;
}