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
struct task_struct {int dummy; } ;
struct pid {int dummy; } ;
struct TYPE_2__ {struct task_struct* group_leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PGID ; 
 int /*<<< orphan*/  PIDTYPE_SID ; 
 int /*<<< orphan*/  change_pid (struct task_struct*,int /*<<< orphan*/ ,struct pid*) ; 
 TYPE_1__* current ; 
 struct pid* task_pgrp (struct task_struct*) ; 
 struct pid* task_session (struct task_struct*) ; 

void __set_special_pids(struct pid *pid)
{
	struct task_struct *curr = current->group_leader;

	if (task_session(curr) != pid)
		change_pid(curr, PIDTYPE_SID, pid);

	if (task_pgrp(curr) != pid)
		change_pid(curr, PIDTYPE_PGID, pid);
}