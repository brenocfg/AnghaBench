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
struct cgroup {int dummy; } ;

/* Variables and functions */
 scalar_t__ cgroup_is_removed (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool cgroup_lock_live_group(struct cgroup *cgrp)
{
	mutex_lock(&cgroup_mutex);
	if (cgroup_is_removed(cgrp)) {
		mutex_unlock(&cgroup_mutex);
		return false;
	}
	return true;
}