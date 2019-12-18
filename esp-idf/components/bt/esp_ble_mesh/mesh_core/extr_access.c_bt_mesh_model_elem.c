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
struct bt_mesh_model {size_t elem_idx; } ;
struct bt_mesh_elem {int dummy; } ;
struct TYPE_2__ {struct bt_mesh_elem* elem; } ;

/* Variables and functions */
 TYPE_1__* dev_comp ; 

struct bt_mesh_elem *bt_mesh_model_elem(struct bt_mesh_model *mod)
{
    return &dev_comp->elem[mod->elem_idx];
}