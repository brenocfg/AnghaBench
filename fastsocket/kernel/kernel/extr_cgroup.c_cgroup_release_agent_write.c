#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgroup {TYPE_1__* root; } ;
struct cftype {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  release_agent_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENODEV ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  cgroup_lock_live_group (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_root_mutex ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int cgroup_release_agent_write(struct cgroup *cgrp, struct cftype *cft,
				      const char *buffer)
{
	BUILD_BUG_ON(sizeof(cgrp->root->release_agent_path) < PATH_MAX);
	if (!cgroup_lock_live_group(cgrp))
		return -ENODEV;
	mutex_lock(&cgroup_root_mutex);
	strcpy(cgrp->root->release_agent_path, buffer);
	mutex_unlock(&cgroup_root_mutex);
	cgroup_unlock();
	return 0;
}