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
struct bt_mesh_app_key {int dummy; } ;

/* Variables and functions */
 scalar_t__ FAST_PROV ; 
 scalar_t__ NODE ; 
 scalar_t__ PROVISIONER ; 
 struct bt_mesh_app_key* bt_mesh_app_key_find (int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 scalar_t__ bt_mesh_is_provisioner_en () ; 
 struct bt_mesh_app_key* fast_prov_app_key_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bt_mesh_app_key* provisioner_app_key_find (int /*<<< orphan*/ ) ; 

struct bt_mesh_app_key *bt_mesh_tx_appkey_get(u8_t role, u16_t app_idx, u16_t net_idx)
{
    struct bt_mesh_app_key *key = NULL;

#if CONFIG_BLE_MESH_NODE && !CONFIG_BLE_MESH_PROVISIONER
    if (role == NODE) {
        if (bt_mesh_is_provisioned()) {
            key = bt_mesh_app_key_find(app_idx);
        }
    }
#endif

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (role == PROVISIONER) {
        if (bt_mesh_is_provisioner_en()) {
            key = provisioner_app_key_find(app_idx);
        }
    }
#endif

#if CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    if (role == NODE) {
        if (bt_mesh_is_provisioned()) {
            key = bt_mesh_app_key_find(app_idx);
        }
    } else if (role == PROVISIONER) {
        if (bt_mesh_is_provisioner_en()) {
            key = provisioner_app_key_find(app_idx);
        }
    } else if (role == FAST_PROV) {
#if CONFIG_BLE_MESH_FAST_PROV
        key = fast_prov_app_key_find(net_idx, app_idx);
#endif
    }
#endif

    return key;
}