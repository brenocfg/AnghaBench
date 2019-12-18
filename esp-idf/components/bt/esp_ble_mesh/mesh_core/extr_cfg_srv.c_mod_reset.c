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
struct bt_mesh_model {int dummy; } ;
struct bt_mesh_elem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_store_mod_sub (struct bt_mesh_model*) ; 
 size_t mod_sub_list_clear (struct bt_mesh_model*) ; 

__attribute__((used)) static void mod_reset(struct bt_mesh_model *mod, struct bt_mesh_elem *elem,
                      bool vnd, bool primary, void *user_data)
{
    size_t clear_count;

    /* Clear model state that isn't otherwise cleared. E.g. AppKey
     * binding and model publication is cleared as a consequence
     * of removing all app keys, however model subscription clearing
     * must be taken care of here.
     */

    clear_count = mod_sub_list_clear(mod);

    if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS) && clear_count) {
        bt_mesh_store_mod_sub(mod);
    }
}