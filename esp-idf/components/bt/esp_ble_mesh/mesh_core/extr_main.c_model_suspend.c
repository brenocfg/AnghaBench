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
struct bt_mesh_model {TYPE_1__* pub; } ;
struct bt_mesh_elem {int dummy; } ;
struct TYPE_2__ {unsigned int count; int /*<<< orphan*/  timer; scalar_t__ update; } ;

/* Variables and functions */
 int /*<<< orphan*/  k_delayed_work_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void model_suspend(struct bt_mesh_model *mod, struct bt_mesh_elem *elem,
                          bool vnd, bool primary, void *user_data)
{
    if (mod->pub && mod->pub->update) {
        mod->pub->count = 0U;
        k_delayed_work_cancel(&mod->pub->timer);
    }
}