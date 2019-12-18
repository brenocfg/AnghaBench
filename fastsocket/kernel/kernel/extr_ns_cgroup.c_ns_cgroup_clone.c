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
struct pid {int dummy; } ;

/* Variables and functions */
 int PROC_NUMBUF ; 
 int cgroup_clone (struct task_struct*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ns_subsys ; 
 int pid_vnr (struct pid*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int ns_cgroup_clone(struct task_struct *task, struct pid *pid)
{
	char name[PROC_NUMBUF];

	snprintf(name, PROC_NUMBUF, "%d", pid_vnr(pid));
	return cgroup_clone(task, &ns_subsys, name);
}