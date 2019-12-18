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
struct bt_mesh_model {scalar_t__ id; } ;
struct bt_mesh_elem {size_t model_count; struct bt_mesh_model* models; } ;

/* Variables and functions */

struct bt_mesh_model *bt_mesh_model_find(struct bt_mesh_elem *elem,
        u16_t id)
{
    u8_t i;

    for (i = 0U; i < elem->model_count; i++) {
        if (elem->models[i].id == id) {
            return &elem->models[i];
        }
    }

    return NULL;
}