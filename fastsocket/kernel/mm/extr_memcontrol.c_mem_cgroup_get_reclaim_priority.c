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
struct mem_cgroup {int prev_priority; int /*<<< orphan*/  reclaim_param_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mem_cgroup_get_reclaim_priority(struct mem_cgroup *mem)
{
	int prev_priority;

	spin_lock(&mem->reclaim_param_lock);
	prev_priority = mem->prev_priority;
	spin_unlock(&mem->reclaim_param_lock);

	return prev_priority;
}