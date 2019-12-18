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
struct pid_namespace {int hide_pid; int /*<<< orphan*/  pid_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_MODE_READ ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 
 int ptrace_may_access (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has_pid_permissions(struct pid_namespace *pid,
				 struct task_struct *task,
				 int hide_pid_min)
{
	if (pid->hide_pid < hide_pid_min)
		return true;
	if (in_group_p(pid->pid_gid))
		return true;
	return ptrace_may_access(task, PTRACE_MODE_READ);
}