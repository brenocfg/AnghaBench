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
 int EAGAIN ; 
 int attach_task_by_pid (struct cgroup*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cgroup_procs_write(struct cgroup *cgrp, struct cftype *cft, u64 tgid)
{
	int ret;
	do {
		/*
		 * attach_proc fails with -EAGAIN if threadgroup leadership
		 * changes in the middle of the operation, in which case we need
		 * to find the task_struct for the new leader and start over.
		 */
		ret = attach_task_by_pid(cgrp, tgid, true);
	} while (ret == -EAGAIN);
	return ret;
}