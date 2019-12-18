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
struct task {int dummy; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 struct task* current_task () ; 
 struct proc* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (struct proc*) ; 
 struct proc* proc_self () ; 
 struct task* proc_task (struct proc*) ; 
 int task_pid (struct task*) ; 

__attribute__((used)) static struct proc *
mac_task_get_proc(struct task *task)
{
	if (task == current_task())
		return proc_self();

	/*
	 * Tasks don't really hold a reference on a proc unless the
	 * calling thread belongs to the task in question.
	 */
	int pid = task_pid(task);
	struct proc *p = proc_find(pid);

	if (p != NULL) {
		if (proc_task(p) == task)
			return p;
		proc_rele(p);
	}
	return NULL;
}