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
struct bt_mesh_subnet {int /*<<< orphan*/  net_idx; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_GATT_PROXY_ENABLED ; 
 int /*<<< orphan*/  BLE_MESH_KEY_ANY ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_FRIEND ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_GATT_PROXY_SERVER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_friend_sec_update (int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_gatt_proxy_get () ; 
 int /*<<< orphan*/  bt_mesh_proxy_beacon_send (struct bt_mesh_subnet*) ; 

void bt_mesh_net_sec_update(struct bt_mesh_subnet *sub)
{
    if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND)) {
        bt_mesh_friend_sec_update(sub ? sub->net_idx : BLE_MESH_KEY_ANY);
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_GATT_PROXY_SERVER) &&
            bt_mesh_gatt_proxy_get() == BLE_MESH_GATT_PROXY_ENABLED) {
#if CONFIG_BLE_MESH_NODE
        bt_mesh_proxy_beacon_send(sub);
#endif
    }
}