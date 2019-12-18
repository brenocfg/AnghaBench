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
struct cgroup_subsys {int dummy; } ;
struct cgroup {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cft_memory_pressure_enabled ; 
 int cgroup_add_file (struct cgroup*,struct cgroup_subsys*,int /*<<< orphan*/ *) ; 
 int cgroup_add_files (struct cgroup*,struct cgroup_subsys*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files ; 

__attribute__((used)) static int cpuset_populate(struct cgroup_subsys *ss, struct cgroup *cont)
{
	int err;

	err = cgroup_add_files(cont, ss, files, ARRAY_SIZE(files));
	if (err)
		return err;
	/* memory_pressure_enabled is in root cpuset only */
	if (!cont->parent)
		err = cgroup_add_file(cont, ss,
				      &cft_memory_pressure_enabled);
	return err;
}