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
struct task_struct {int dummy; } ;
struct cgroup_subsys {int /*<<< orphan*/  (* fork ) (struct cgroup_subsys*,struct task_struct*) ;} ;

/* Variables and functions */
 int CGROUP_SUBSYS_COUNT ; 
 scalar_t__ need_forkexit_callback ; 
 int /*<<< orphan*/  stub1 (struct cgroup_subsys*,struct task_struct*) ; 
 struct cgroup_subsys** subsys ; 

void cgroup_fork_callbacks(struct task_struct *child)
{
	if (need_forkexit_callback) {
		int i;
		for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
			struct cgroup_subsys *ss = subsys[i];
			if (ss->fork)
				ss->fork(ss, child);
		}
	}
}