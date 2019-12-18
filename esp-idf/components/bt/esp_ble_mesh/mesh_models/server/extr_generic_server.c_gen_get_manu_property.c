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
typedef  size_t u8_t ;
typedef  scalar_t__ u16_t ;
struct bt_mesh_model {struct bt_mesh_gen_manu_prop_srv* user_data; } ;
struct bt_mesh_generic_property {scalar_t__ id; } ;
struct bt_mesh_gen_manu_prop_srv {size_t property_count; struct bt_mesh_generic_property* properties; } ;

/* Variables and functions */

struct bt_mesh_generic_property *gen_get_manu_property(struct bt_mesh_model *model,
        u16_t property_id)
{
    struct bt_mesh_gen_manu_prop_srv *srv = model->user_data;
    u8_t i;

    for (i = 0U; i < srv->property_count; i++) {
        if (srv->properties[i].id == property_id) {
            return &srv->properties[i];
        }
    }

    return NULL;
}