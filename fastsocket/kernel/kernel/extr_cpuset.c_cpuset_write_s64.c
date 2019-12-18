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
typedef  int /*<<< orphan*/  s64 ;
typedef  int cpuset_filetype_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  FILE_SCHED_RELAX_DOMAIN_LEVEL 128 
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_lock_live_group (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 int update_relax_domain_level (struct cpuset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpuset_write_s64(struct cgroup *cgrp, struct cftype *cft, s64 val)
{
	int retval = 0;
	struct cpuset *cs = cgroup_cs(cgrp);
	cpuset_filetype_t type = cft->private;

	if (!cgroup_lock_live_group(cgrp))
		return -ENODEV;

	switch (type) {
	case FILE_SCHED_RELAX_DOMAIN_LEVEL:
		retval = update_relax_domain_level(cs, val);
		break;
	default:
		retval = -EINVAL;
		break;
	}
	cgroup_unlock();
	return retval;
}