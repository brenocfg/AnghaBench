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
struct cftype {int private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
#define  FILE_CPULIST 129 
#define  FILE_MEMLIST 128 
 struct cpuset* alloc_trial_cpuset (struct cpuset*) ; 
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_lock_live_group (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 int /*<<< orphan*/  free_trial_cpuset (struct cpuset*) ; 
 int update_cpumask (struct cpuset*,struct cpuset*,char const*) ; 
 int update_nodemask (struct cpuset*,struct cpuset*,char const*) ; 

__attribute__((used)) static int cpuset_write_resmask(struct cgroup *cgrp, struct cftype *cft,
				const char *buf)
{
	int retval = 0;
	struct cpuset *cs = cgroup_cs(cgrp);
	struct cpuset *trialcs;

	if (!cgroup_lock_live_group(cgrp))
		return -ENODEV;

	trialcs = alloc_trial_cpuset(cs);
	if (!trialcs) {
		retval = -ENOMEM;
		goto out;
	}

	switch (cft->private) {
	case FILE_CPULIST:
		retval = update_cpumask(cs, trialcs, buf);
		break;
	case FILE_MEMLIST:
		retval = update_nodemask(cs, trialcs, buf);
		break;
	default:
		retval = -EINVAL;
		break;
	}

	free_trial_cpuset(trialcs);
out:
	cgroup_unlock();
	return retval;
}