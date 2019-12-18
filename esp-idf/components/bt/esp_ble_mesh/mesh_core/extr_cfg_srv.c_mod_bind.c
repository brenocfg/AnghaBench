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
struct bt_mesh_model {scalar_t__* keys; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ BLE_MESH_KEY_UNUSED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct bt_mesh_model*,scalar_t__) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INSUFF_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_APPKEY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  app_key_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  bt_mesh_store_mod_bind (struct bt_mesh_model*) ; 

__attribute__((used)) static u8_t mod_bind(struct bt_mesh_model *model, u16_t key_idx)
{
    int i;

    BT_DBG("model %p key_idx 0x%03x", model, key_idx);

    if (!app_key_is_valid(key_idx)) {
        return STATUS_INVALID_APPKEY;
    }

    for (i = 0; i < ARRAY_SIZE(model->keys); i++) {
        /* Treat existing binding as success */
        if (model->keys[i] == key_idx) {
            return STATUS_SUCCESS;
        }
    }

    for (i = 0; i < ARRAY_SIZE(model->keys); i++) {
        if (model->keys[i] == BLE_MESH_KEY_UNUSED) {
            model->keys[i] = key_idx;

            if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS)) {
                bt_mesh_store_mod_bind(model);
            }

            return STATUS_SUCCESS;
        }
    }

    return STATUS_INSUFF_RESOURCES;
}