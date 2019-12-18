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
struct mem_cgroup_tree_per_zone {int /*<<< orphan*/  lock; } ;
struct mem_cgroup_per_zone {int dummy; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_cgroup_remove_exceeded (struct mem_cgroup*,struct mem_cgroup_per_zone*,struct mem_cgroup_tree_per_zone*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mem_cgroup_remove_exceeded(struct mem_cgroup *mem,
				struct mem_cgroup_per_zone *mz,
				struct mem_cgroup_tree_per_zone *mctz)
{
	spin_lock(&mctz->lock);
	__mem_cgroup_remove_exceeded(mem, mz, mctz);
	spin_unlock(&mctz->lock);
}