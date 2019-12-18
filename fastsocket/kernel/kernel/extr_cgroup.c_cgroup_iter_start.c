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
struct cgroup_iter {int /*<<< orphan*/ * cg_link; } ;
struct cgroup {int /*<<< orphan*/  css_sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_advance_iter (struct cgroup*,struct cgroup_iter*) ; 
 int /*<<< orphan*/  cgroup_enable_task_cg_lists () ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_task_css_set_links ; 

void cgroup_iter_start(struct cgroup *cgrp, struct cgroup_iter *it)
{
	/*
	 * The first time anyone tries to iterate across a cgroup,
	 * we need to enable the list linking each css_set to its
	 * tasks, and fix up all existing tasks.
	 */
	if (!use_task_css_set_links)
		cgroup_enable_task_cg_lists();

	read_lock(&css_set_lock);
	it->cg_link = &cgrp->css_sets;
	cgroup_advance_iter(cgrp, it);
}