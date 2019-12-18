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
struct css_id {size_t depth; scalar_t__* stack; scalar_t__ id; } ;
struct cgroup_subsys_state {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct css_id* rcu_dereference (int /*<<< orphan*/ ) ; 

bool css_is_ancestor(struct cgroup_subsys_state *child,
		    const struct cgroup_subsys_state *root)
{
	struct css_id *child_id = rcu_dereference(child->id);
	struct css_id *root_id = rcu_dereference(root->id);

	if (!child_id || !root_id || (child_id->depth < root_id->depth))
		return false;
	return child_id->stack[root_id->depth] == root_id->id;
}