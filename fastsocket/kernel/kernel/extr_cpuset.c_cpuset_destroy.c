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
struct cpuset {int /*<<< orphan*/  cpus_allowed; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SCHED_LOAD_BALANCE ; 
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 scalar_t__ is_sched_load_balance (struct cpuset*) ; 
 int /*<<< orphan*/  kfree (struct cpuset*) ; 
 int /*<<< orphan*/  number_of_cpusets ; 
 int /*<<< orphan*/  update_flag (int /*<<< orphan*/ ,struct cpuset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuset_destroy(struct cgroup_subsys *ss, struct cgroup *cont)
{
	struct cpuset *cs = cgroup_cs(cont);

	if (is_sched_load_balance(cs))
		update_flag(CS_SCHED_LOAD_BALANCE, cs, 0);

	number_of_cpusets--;
	free_cpumask_var(cs->cpus_allowed);
	kfree(cs);
}