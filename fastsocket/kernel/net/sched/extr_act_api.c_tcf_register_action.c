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
struct tc_action_ops {scalar_t__ type; struct tc_action_ops* next; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int EEXIST ; 
 struct tc_action_ops* act_base ; 
 int /*<<< orphan*/  act_mod_lock ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int tcf_register_action(struct tc_action_ops *act)
{
	struct tc_action_ops *a, **ap;

	write_lock(&act_mod_lock);
	for (ap = &act_base; (a = *ap) != NULL; ap = &a->next) {
		if (act->type == a->type || (strcmp(act->kind, a->kind) == 0)) {
			write_unlock(&act_mod_lock);
			return -EEXIST;
		}
	}
	act->next = NULL;
	*ap = act;
	write_unlock(&act_mod_lock);
	return 0;
}