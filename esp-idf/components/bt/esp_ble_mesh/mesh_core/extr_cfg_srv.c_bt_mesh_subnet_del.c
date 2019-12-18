#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bt_mesh_subnet {scalar_t__ net_idx; } ;
struct bt_mesh_app_key {scalar_t__ net_idx; } ;
struct TYPE_7__ {struct bt_mesh_app_key* app_keys; } ;
struct TYPE_5__ {scalar_t__ net_idx; } ;
struct TYPE_6__ {TYPE_1__ hb_pub; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bt_mesh_app_key*) ; 
 scalar_t__ BLE_MESH_KEY_UNUSED ; 
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_FRIEND ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_4__ bt_mesh ; 
 int /*<<< orphan*/  bt_mesh_app_key_del (struct bt_mesh_app_key*,int) ; 
 int /*<<< orphan*/  bt_mesh_clear_subnet (struct bt_mesh_subnet*) ; 
 int /*<<< orphan*/  bt_mesh_friend_clear_net_idx (scalar_t__) ; 
 int /*<<< orphan*/  bt_mesh_store_hb_pub () ; 
 TYPE_2__* conf ; 
 int /*<<< orphan*/  hb_pub_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (struct bt_mesh_subnet*,int /*<<< orphan*/ ,int) ; 

void bt_mesh_subnet_del(struct bt_mesh_subnet *sub, bool store)
{
    int i;

    BT_DBG("NetIdx 0x%03x store %u", sub->net_idx, store);

    if (conf && conf->hb_pub.net_idx == sub->net_idx) {
        hb_pub_disable(conf);

        if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS) && store) {
            bt_mesh_store_hb_pub();
        }
    }

    /* Delete any app keys bound to this NetKey index */
    for (i = 0; i < ARRAY_SIZE(bt_mesh.app_keys); i++) {
        struct bt_mesh_app_key *key = &bt_mesh.app_keys[i];

        if (key->net_idx == sub->net_idx) {
            bt_mesh_app_key_del(key, store);
        }
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND)) {
        bt_mesh_friend_clear_net_idx(sub->net_idx);
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS) && store) {
        bt_mesh_clear_subnet(sub);
    }

    (void)memset(sub, 0, sizeof(*sub));
    sub->net_idx = BLE_MESH_KEY_UNUSED;
}