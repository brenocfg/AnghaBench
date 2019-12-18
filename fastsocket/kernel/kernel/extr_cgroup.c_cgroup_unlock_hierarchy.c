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
struct cgroupfs_root {int dummy; } ;
struct cgroup_subsys {int /*<<< orphan*/  hierarchy_mutex; struct cgroupfs_root* root; } ;

/* Variables and functions */
 int CGROUP_SUBSYS_COUNT ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cgroup_subsys** subsys ; 

__attribute__((used)) static void cgroup_unlock_hierarchy(struct cgroupfs_root *root)
{
	int i;

	for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
		struct cgroup_subsys *ss = subsys[i];
		if (ss->root == root)
			mutex_unlock(&ss->hierarchy_mutex);
	}
}