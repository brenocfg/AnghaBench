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
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_is_descendant (struct cgroup*,struct task_struct*) ; 
 struct task_struct* current ; 

__attribute__((used)) static int ns_can_attach(struct cgroup_subsys *ss, struct cgroup *new_cgroup,
			 struct task_struct *task)
{
	if (current != task) {
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;

		if (!cgroup_is_descendant(new_cgroup, current))
			return -EPERM;
	}

	return 0;
}