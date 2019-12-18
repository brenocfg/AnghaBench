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
struct dev_cgroup {int dummy; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 struct dev_cgroup* cgroup_to_devcgroup (struct cgroup*) ; 
 int /*<<< orphan*/  dev_exception_clean (struct dev_cgroup*) ; 
 int /*<<< orphan*/  kfree (struct dev_cgroup*) ; 

__attribute__((used)) static void devcgroup_destroy(struct cgroup_subsys *ss,
			struct cgroup *cgroup)
{
	struct dev_cgroup *dev_cgroup;

	dev_cgroup = cgroup_to_devcgroup(cgroup);
	dev_exception_clean(dev_cgroup);
	kfree(dev_cgroup);
}