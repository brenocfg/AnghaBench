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
typedef  scalar_t__ s32_t ;
struct TYPE_2__ {int /*<<< orphan*/  timer; scalar_t__ update; } ;

/* Variables and functions */
 scalar_t__ bt_mesh_model_pub_period_get (struct bt_mesh_model*) ; 
 int /*<<< orphan*/  k_delayed_work_submit (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void model_resume(struct bt_mesh_model *mod, struct bt_mesh_elem *elem,
                         bool vnd, bool primary, void *user_data)
{
    if (mod->pub && mod->pub->update) {
        s32_t period_ms = bt_mesh_model_pub_period_get(mod);

        if (period_ms) {
            k_delayed_work_submit(&mod->pub->timer, period_ms);
        }
    }
}