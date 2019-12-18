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
struct bt_mesh_comp {int /*<<< orphan*/  elem_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bt_mesh_model_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bt_mesh_comp const* dev_comp ; 
 int /*<<< orphan*/  mod_init ; 

int bt_mesh_comp_register(const struct bt_mesh_comp *comp)
{
    /* There must be at least one element */
    if (!comp->elem_count) {
        return -EINVAL;
    }

    dev_comp = comp;

    bt_mesh_model_foreach(mod_init, NULL);

    return 0;
}