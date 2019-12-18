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
struct cgroup {int dummy; } ;

/* Variables and functions */
 int security_task_setscheduler (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpuset_can_attach_task(struct cgroup *cgrp, struct task_struct *task)
{
	return security_task_setscheduler(task, 0, NULL);
}