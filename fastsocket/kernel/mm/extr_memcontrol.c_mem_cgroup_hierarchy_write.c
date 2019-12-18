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
typedef  int u64 ;
struct mem_cgroup {int use_hierarchy; } ;
struct cgroup {int /*<<< orphan*/  children; struct cgroup* parent; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  cgroup_lock () ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 

__attribute__((used)) static int mem_cgroup_hierarchy_write(struct cgroup *cont, struct cftype *cft,
					u64 val)
{
	int retval = 0;
	struct mem_cgroup *mem = mem_cgroup_from_cont(cont);
	struct cgroup *parent = cont->parent;
	struct mem_cgroup *parent_mem = NULL;

	if (parent)
		parent_mem = mem_cgroup_from_cont(parent);

	cgroup_lock();
	/*
	 * If parent's use_hiearchy is set, we can't make any modifications
	 * in the child subtrees. If it is unset, then the change can
	 * occur, provided the current cgroup has no children.
	 *
	 * For the root cgroup, parent_mem is NULL, we allow value to be
	 * set if there are no children.
	 */
	if ((!parent_mem || !parent_mem->use_hierarchy) &&
				(val == 1 || val == 0)) {
		if (list_empty(&cont->children))
			mem->use_hierarchy = val;
		else
			retval = -EBUSY;
	} else
		retval = -EINVAL;
	cgroup_unlock();

	return retval;
}