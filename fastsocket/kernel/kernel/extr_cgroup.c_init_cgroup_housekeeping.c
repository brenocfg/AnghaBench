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
struct cgroup {int /*<<< orphan*/  event_list_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  pidlist_mutex; int /*<<< orphan*/  pidlists; int /*<<< orphan*/  release_list; int /*<<< orphan*/  css_sets; int /*<<< orphan*/  children; int /*<<< orphan*/  sibling; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_cgroup_housekeeping(struct cgroup *cgrp)
{
	INIT_LIST_HEAD(&cgrp->sibling);
	INIT_LIST_HEAD(&cgrp->children);
	INIT_LIST_HEAD(&cgrp->css_sets);
	INIT_LIST_HEAD(&cgrp->release_list);
	INIT_LIST_HEAD(&cgrp->pidlists);
	mutex_init(&cgrp->pidlist_mutex);
	INIT_LIST_HEAD(&cgrp->event_list);
	spin_lock_init(&cgrp->event_list_lock);
}