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
typedef  int /*<<< orphan*/  u64 ;
struct cgroup {int dummy; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int attach_task_by_pid (struct cgroup*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cgroup_tasks_write(struct cgroup *cgrp, struct cftype *cft, u64 pid)
{
	return attach_task_by_pid(cgrp, pid, false);
}