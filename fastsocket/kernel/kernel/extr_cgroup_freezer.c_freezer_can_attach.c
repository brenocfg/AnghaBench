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
struct task_struct {int dummy; } ;
struct freezer {scalar_t__ state; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 scalar_t__ CGROUP_THAWED ; 
 int EBUSY ; 
 struct freezer* cgroup_freezer (struct cgroup*) ; 

__attribute__((used)) static int freezer_can_attach(struct cgroup_subsys *ss,
			      struct cgroup *new_cgroup,
			      struct task_struct *task)
{
	struct freezer *freezer;

	/*
	 * Anything frozen can't move or be moved to/from.
	 */

	freezer = cgroup_freezer(new_cgroup);
	if (freezer->state != CGROUP_THAWED)
		return -EBUSY;

	return 0;
}