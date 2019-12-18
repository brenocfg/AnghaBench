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
struct mm_struct {int dummy; } ;
struct cpuset {int /*<<< orphan*/  mems_allowed; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 int /*<<< orphan*/  cpuset_attach_nodemask_from ; 
 int /*<<< orphan*/  cpuset_attach_nodemask_to ; 
 int /*<<< orphan*/  cpuset_migrate_mm (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 scalar_t__ is_memory_migrate (struct cpuset*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  mpol_rebind_mm (struct mm_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuset_attach(struct cgroup_subsys *ss, struct cgroup *cont,
			  struct cgroup *oldcont, struct task_struct *tsk)
{
	struct mm_struct *mm;
	struct cpuset *cs = cgroup_cs(cont);
	struct cpuset *oldcs = cgroup_cs(oldcont);

	/*
	 * Change mm, possibly for multiple threads in a threadgroup. This is
	 * expensive and may sleep.
	 */
	cpuset_attach_nodemask_from = oldcs->mems_allowed;
	cpuset_attach_nodemask_to = cs->mems_allowed;
	mm = get_task_mm(tsk);
	if (mm) {
		mpol_rebind_mm(mm, &cpuset_attach_nodemask_to);
		if (is_memory_migrate(cs))
			cpuset_migrate_mm(mm, &cpuset_attach_nodemask_from,
					  &cpuset_attach_nodemask_to);
		mmput(mm);
	}
}