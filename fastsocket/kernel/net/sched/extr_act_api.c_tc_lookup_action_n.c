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
struct tc_action_ops {int /*<<< orphan*/  owner; int /*<<< orphan*/  kind; struct tc_action_ops* next; } ;

/* Variables and functions */
 struct tc_action_ops* act_base ; 
 int /*<<< orphan*/  act_mod_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tc_action_ops *tc_lookup_action_n(char *kind)
{
	struct tc_action_ops *a = NULL;

	if (kind) {
		read_lock(&act_mod_lock);
		for (a = act_base; a; a = a->next) {
			if (strcmp(kind, a->kind) == 0) {
				if (!try_module_get(a->owner)) {
					read_unlock(&act_mod_lock);
					return NULL;
				}
				break;
			}
		}
		read_unlock(&act_mod_lock);
	}
	return a;
}