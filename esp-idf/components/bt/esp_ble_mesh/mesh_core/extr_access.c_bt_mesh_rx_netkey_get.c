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
struct bt_mesh_subnet {int dummy; } ;
struct TYPE_2__ {struct bt_mesh_subnet* sub; struct bt_mesh_subnet** p_sub; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct bt_mesh_subnet*) ; 
 TYPE_1__ bt_mesh ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_is_provisioner_en () ; 

struct bt_mesh_subnet *bt_mesh_rx_netkey_get(size_t index)
{
    struct bt_mesh_subnet *sub = NULL;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioned()) {
        sub = &bt_mesh.sub[index];
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (bt_mesh_is_provisioner_en()) {
        sub = bt_mesh.p_sub[index];
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (index < ARRAY_SIZE(bt_mesh.sub)) {
        sub = &bt_mesh.sub[index];
    } else {
        sub = bt_mesh.p_sub[index - ARRAY_SIZE(bt_mesh.sub)];
    }
#endif

    return sub;
}