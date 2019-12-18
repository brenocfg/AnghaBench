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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
struct bt_mesh_subnet {scalar_t__ net_idx; scalar_t__ kr_phase; int /*<<< orphan*/ * keys; } ;
struct TYPE_2__ {struct bt_mesh_subnet* sub; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bt_mesh_subnet*) ; 
 scalar_t__ BLE_MESH_KEY_UNUSED ; 
 scalar_t__ BLE_MESH_KR_NORMAL ; 
 scalar_t__ auth_match (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 TYPE_1__ bt_mesh ; 

struct bt_mesh_subnet *bt_mesh_subnet_find(const u8_t net_id[8], u8_t flags,
        u32_t iv_index, const u8_t auth[8],
        bool *new_key)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(bt_mesh.sub); i++) {
        struct bt_mesh_subnet *sub = &bt_mesh.sub[i];

        if (sub->net_idx == BLE_MESH_KEY_UNUSED) {
            continue;
        }

        if (auth_match(&sub->keys[0], net_id, flags, iv_index, auth)) {
            *new_key = false;
            return sub;
        }

        if (sub->kr_phase == BLE_MESH_KR_NORMAL) {
            continue;
        }

        if (auth_match(&sub->keys[1], net_id, flags, iv_index, auth)) {
            *new_key = true;
            return sub;
        }
    }

    return NULL;
}