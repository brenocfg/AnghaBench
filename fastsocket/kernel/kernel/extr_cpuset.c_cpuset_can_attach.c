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
struct task_struct {int flags; } ;
struct cpuset {int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  cpus_allowed; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int PF_THREAD_BOUND ; 
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ nodes_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpuset_can_attach(struct cgroup_subsys *ss, struct cgroup *cont,
			     struct task_struct *tsk)
{
	struct cpuset *cs = cgroup_cs(cont);

	if (cpumask_empty(cs->cpus_allowed) || nodes_empty(cs->mems_allowed))
		return -ENOSPC;

	/*
	 * Kthreads bound to specific cpus cannot be moved to a new cpuset; we
	 * cannot change their cpu affinity and isolating such threads by their
	 * set of allowed nodes is unnecessary.  Thus, cpusets are not
	 * applicable for such threads.  This prevents checking for success of
	 * set_cpus_allowed_ptr() on all attached tasks before cpus_allowed may
	 * be changed.
	 */
	if (tsk->flags & PF_THREAD_BOUND)
		return -EINVAL;

	return 0;
}