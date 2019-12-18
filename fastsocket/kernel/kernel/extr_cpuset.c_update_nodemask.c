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
struct ptr_heap {int dummy; } ;
struct cpuset {int /*<<< orphan*/  mems_allowed; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t N_HIGH_MEMORY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  callback_mutex ; 
 int /*<<< orphan*/  heap_free (struct ptr_heap*) ; 
 int heap_init (struct ptr_heap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * node_states ; 
 int nodelist_parse (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ nodes_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpuset top_cpuset ; 
 int /*<<< orphan*/  update_tasks_nodemask (struct cpuset*,int /*<<< orphan*/ *,struct ptr_heap*) ; 
 int validate_change (struct cpuset*,struct cpuset*) ; 

__attribute__((used)) static int update_nodemask(struct cpuset *cs, struct cpuset *trialcs,
			   const char *buf)
{
	nodemask_t oldmem;
	int retval;
	struct ptr_heap heap;

	/*
	 * top_cpuset.mems_allowed tracks node_stats[N_HIGH_MEMORY];
	 * it's read-only
	 */
	if (cs == &top_cpuset)
		return -EACCES;

	/*
	 * An empty mems_allowed is ok iff there are no tasks in the cpuset.
	 * Since nodelist_parse() fails on an empty mask, we special case
	 * that parsing.  The validate_change() call ensures that cpusets
	 * with tasks have memory.
	 */
	if (!*buf) {
		nodes_clear(trialcs->mems_allowed);
	} else {
		retval = nodelist_parse(buf, trialcs->mems_allowed);
		if (retval < 0)
			goto done;

		if (!nodes_subset(trialcs->mems_allowed,
				node_states[N_HIGH_MEMORY]))
			return -EINVAL;
	}
	oldmem = cs->mems_allowed;
	if (nodes_equal(oldmem, trialcs->mems_allowed)) {
		retval = 0;		/* Too easy - nothing to do */
		goto done;
	}
	retval = validate_change(cs, trialcs);
	if (retval < 0)
		goto done;

	retval = heap_init(&heap, PAGE_SIZE, GFP_KERNEL, NULL);
	if (retval < 0)
		goto done;

	mutex_lock(&callback_mutex);
	cs->mems_allowed = trialcs->mems_allowed;
	mutex_unlock(&callback_mutex);

	update_tasks_nodemask(cs, &oldmem, &heap);

	heap_free(&heap);
done:
	return retval;
}