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
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_subnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ FAST_PROV ; 
 scalar_t__ NODE ; 
 scalar_t__ PROVISIONER ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_is_provisioner_en () ; 
 struct bt_mesh_subnet* bt_mesh_subnet_get (int /*<<< orphan*/ ) ; 
 struct bt_mesh_subnet* fast_prov_subnet_get (int /*<<< orphan*/ ) ; 
 struct bt_mesh_subnet* provisioner_subnet_get (int /*<<< orphan*/ ) ; 

struct bt_mesh_subnet *bt_mesh_tx_netkey_get(u8_t role, u16_t net_idx)
{
    struct bt_mesh_subnet *sub = NULL;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (role == NODE) {
        if (bt_mesh_is_provisioned()) {
            sub = bt_mesh_subnet_get(net_idx);
        }
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (role == PROVISIONER) {
        if (bt_mesh_is_provisioner_en()) {
            sub = provisioner_subnet_get(net_idx);
        }
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (role == NODE) {
        if (bt_mesh_is_provisioned()) {
            sub = bt_mesh_subnet_get(net_idx);
        }
    } else if (role == PROVISIONER) {
        if (bt_mesh_is_provisioner_en()) {
            sub = provisioner_subnet_get(net_idx);
        }
    } else if (role == FAST_PROV) {
#if CONFIG_BLE_MESH_FAST_PROV
        sub = fast_prov_subnet_get(net_idx);
#endif
    }
#endif

    return sub;
}