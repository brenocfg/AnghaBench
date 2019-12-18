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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int cgroup_add_files (struct cgroup*,struct cgroup_subsys*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ss_files ; 

__attribute__((used)) static int cgrp_populate(struct cgroup_subsys *ss, struct cgroup *cgrp)
{
	return cgroup_add_files(cgrp, ss, ss_files, ARRAY_SIZE(ss_files));
}