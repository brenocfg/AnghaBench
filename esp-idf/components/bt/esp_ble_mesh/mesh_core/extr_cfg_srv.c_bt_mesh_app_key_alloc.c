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
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_app_key {scalar_t__ net_idx; } ;
struct TYPE_2__ {struct bt_mesh_app_key* app_keys; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bt_mesh_app_key*) ; 
 scalar_t__ BLE_MESH_KEY_UNUSED ; 
 TYPE_1__ bt_mesh ; 

struct bt_mesh_app_key *bt_mesh_app_key_alloc(u16_t app_idx)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(bt_mesh.app_keys); i++) {
        struct bt_mesh_app_key *key = &bt_mesh.app_keys[i];

        if (key->net_idx == BLE_MESH_KEY_UNUSED) {
            return key;
        }
    }

    return NULL;
}