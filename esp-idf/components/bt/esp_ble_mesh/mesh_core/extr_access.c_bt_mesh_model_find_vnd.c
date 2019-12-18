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
typedef  size_t u8_t ;
typedef  scalar_t__ u16_t ;
struct TYPE_2__ {scalar_t__ company; scalar_t__ id; } ;
struct bt_mesh_model {TYPE_1__ vnd; } ;
struct bt_mesh_elem {size_t vnd_model_count; struct bt_mesh_model* vnd_models; } ;

/* Variables and functions */

struct bt_mesh_model *bt_mesh_model_find_vnd(struct bt_mesh_elem *elem,
        u16_t company, u16_t id)
{
    u8_t i;

    for (i = 0U; i < elem->vnd_model_count; i++) {
        if (elem->vnd_models[i].vnd.company == company &&
                elem->vnd_models[i].vnd.id == id) {
            return &elem->vnd_models[i];
        }
    }

    return NULL;
}