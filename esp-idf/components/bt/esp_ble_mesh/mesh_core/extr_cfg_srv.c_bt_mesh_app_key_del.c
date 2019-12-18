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
struct unbind_data {int store; int /*<<< orphan*/  app_idx; } ;
struct bt_mesh_app_key {int /*<<< orphan*/  keys; int /*<<< orphan*/  net_idx; int /*<<< orphan*/  app_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_KEY_UNUSED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mod_unbind ; 
 int /*<<< orphan*/  bt_mesh_clear_app_key (struct bt_mesh_app_key*) ; 
 int /*<<< orphan*/  bt_mesh_model_foreach (int /*<<< orphan*/ ,struct unbind_data*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void bt_mesh_app_key_del(struct bt_mesh_app_key *key, bool store)
{
    struct unbind_data data = { .app_idx = key->app_idx, .store = store };

    BT_DBG("AppIdx 0x%03x store %u", key->app_idx, store);

    bt_mesh_model_foreach(_mod_unbind, &data);

    if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS) && store) {
        bt_mesh_clear_app_key(key);
    }

    key->net_idx = BLE_MESH_KEY_UNUSED;
    (void)memset(key->keys, 0, sizeof(key->keys));
}