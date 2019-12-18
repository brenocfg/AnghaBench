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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct bt_mesh_subnet {scalar_t__ kr_phase; } ;
struct bt_mesh_app_keys {int /*<<< orphan*/  val; int /*<<< orphan*/  id; } ;
struct bt_mesh_app_key {scalar_t__ net_idx; int updated; scalar_t__ app_idx; struct bt_mesh_app_keys* keys; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_KR_PHASE_1 ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_CANNOT_UPDATE ; 
 int /*<<< orphan*/  STATUS_IDX_ALREADY_STORED ; 
 int /*<<< orphan*/  STATUS_INSUFF_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_APPKEY ; 
 int /*<<< orphan*/  STATUS_INVALID_BINDING ; 
 int /*<<< orphan*/  STATUS_INVALID_NETKEY ; 
 int /*<<< orphan*/  STATUS_STORAGE_FAIL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ bt_mesh_app_id (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 struct bt_mesh_app_key* bt_mesh_app_key_alloc (scalar_t__) ; 
 struct bt_mesh_app_key* bt_mesh_app_key_find (scalar_t__) ; 
 int /*<<< orphan*/  bt_mesh_store_app_key (struct bt_mesh_app_key*) ; 
 struct bt_mesh_subnet* bt_mesh_subnet_get (scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static u8_t app_key_set(u16_t net_idx, u16_t app_idx, const u8_t val[16],
                        bool update)
{
    struct bt_mesh_app_keys *keys;
    struct bt_mesh_app_key *key;
    struct bt_mesh_subnet *sub;

    BT_DBG("net_idx 0x%04x app_idx %04x update %u val %s",
           net_idx, app_idx, update, bt_hex(val, 16));

    sub = bt_mesh_subnet_get(net_idx);
    if (!sub) {
        return STATUS_INVALID_NETKEY;
    }

    key = bt_mesh_app_key_find(app_idx);
    if (update) {
        if (!key) {
            return STATUS_INVALID_APPKEY;
        }

        if (key->net_idx != net_idx) {
            return STATUS_INVALID_BINDING;
        }

        keys = &key->keys[1];

        /* The AppKey Update message shall generate an error when node
         * is in normal operation, Phase 2, or Phase 3 or in Phase 1
         * when the AppKey Update message on a valid AppKeyIndex when
         * the AppKey value is different.
         */
        if (sub->kr_phase != BLE_MESH_KR_PHASE_1) {
            return STATUS_CANNOT_UPDATE;
        }

        if (key->updated) {
            if (memcmp(keys->val, val, 16)) {
                return STATUS_CANNOT_UPDATE;
            } else {
                return STATUS_SUCCESS;
            }
        }

        key->updated = true;
    } else {
        if (key) {
            if (key->net_idx == net_idx &&
                    !memcmp(key->keys[0].val, val, 16)) {
                return STATUS_SUCCESS;
            }

            if (key->net_idx == net_idx) {
                return STATUS_IDX_ALREADY_STORED;
            } else {
                return STATUS_INVALID_NETKEY;
            }
        }

        key = bt_mesh_app_key_alloc(app_idx);
        if (!key) {
            return STATUS_INSUFF_RESOURCES;
        }

        keys = &key->keys[0];
    }

    if (bt_mesh_app_id(val, &keys->id)) {
        if (update) {
            key->updated = false;
        }

        return STATUS_STORAGE_FAIL;
    }

    BT_DBG("app_idx 0x%04x AID 0x%02x", app_idx, keys->id);

    key->net_idx = net_idx;
    key->app_idx = app_idx;
    memcpy(keys->val, val, 16);

    if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS)) {
        BT_DBG("Storing AppKey persistently");
        bt_mesh_store_app_key(key);
    }

    return STATUS_SUCCESS;
}