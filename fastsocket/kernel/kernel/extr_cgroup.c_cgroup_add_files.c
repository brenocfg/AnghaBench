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
struct cgroup {int dummy; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int cgroup_add_file (struct cgroup*,struct cgroup_subsys*,struct cftype const*) ; 

int cgroup_add_files(struct cgroup *cgrp,
			struct cgroup_subsys *subsys,
			const struct cftype cft[],
			int count)
{
	int i, err;
	for (i = 0; i < count; i++) {
		err = cgroup_add_file(cgrp, subsys, &cft[i]);
		if (err)
			return err;
	}
	return 0;
}