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
struct cpuset {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 int /*<<< orphan*/  cpus_attach ; 
 int /*<<< orphan*/  cpuset_attach_nodemask_to ; 
 int /*<<< orphan*/  cpuset_change_task_nodemask (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuset_update_task_spread_flag (struct cpuset*,struct task_struct*) ; 
 int set_cpus_allowed_ptr (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuset_attach_task(struct cgroup *cont, struct task_struct *tsk)
{
	int err;
	struct cpuset *cs = cgroup_cs(cont);

	/*
	 * can_attach beforehand should guarantee that this doesn't fail.
	 * TODO: have a better way to handle failure here
	 */
	err = set_cpus_allowed_ptr(tsk, cpus_attach);
	WARN_ON_ONCE(err);

	cpuset_change_task_nodemask(tsk, &cpuset_attach_nodemask_to);
	cpuset_update_task_spread_flag(cs, tsk);
}