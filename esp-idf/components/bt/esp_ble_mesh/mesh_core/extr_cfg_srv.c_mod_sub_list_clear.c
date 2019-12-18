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
struct bt_mesh_model {scalar_t__* groups; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ BLE_MESH_ADDR_UNASSIGNED ; 

__attribute__((used)) static size_t mod_sub_list_clear(struct bt_mesh_model *mod)
{
    size_t clear_count;
    int i;

    /* Unref stored labels related to this model */
    for (i = 0, clear_count = 0; i < ARRAY_SIZE(mod->groups); i++) {
        if (mod->groups[i] != BLE_MESH_ADDR_UNASSIGNED) {
            mod->groups[i] = BLE_MESH_ADDR_UNASSIGNED;
            clear_count++;
        }
    }

    return clear_count;
}