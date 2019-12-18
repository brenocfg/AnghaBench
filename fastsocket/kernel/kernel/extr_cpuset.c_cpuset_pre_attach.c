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
struct cpuset {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_attach ; 
 int /*<<< orphan*/  cpuset_attach_nodemask_to ; 
 int /*<<< orphan*/  guarantee_online_cpus (struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guarantee_online_mems (struct cpuset*,int /*<<< orphan*/ *) ; 
 struct cpuset top_cpuset ; 

__attribute__((used)) static void cpuset_pre_attach(struct cgroup *cont)
{
	struct cpuset *cs = cgroup_cs(cont);

	if (cs == &top_cpuset)
		cpumask_copy(cpus_attach, cpu_possible_mask);
	else
		guarantee_online_cpus(cs, cpus_attach);

	guarantee_online_mems(cs, &cpuset_attach_nodemask_to);
}