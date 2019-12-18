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
struct task_struct {TYPE_1__* pids; struct task_struct* group_leader; } ;
struct pid {int dummy; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;
struct TYPE_2__ {struct pid* pid; } ;

/* Variables and functions */
 int PIDTYPE_PID ; 

__attribute__((used)) static inline
struct pid *task_pid_type(struct task_struct *task, enum pid_type type)
{
	if (type != PIDTYPE_PID)
		task = task->group_leader;
	return task->pids[type].pid;
}