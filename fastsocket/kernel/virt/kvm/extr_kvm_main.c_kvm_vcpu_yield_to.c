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
struct task_struct {int flags; } ;
struct pid {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int PF_VCPU ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 struct pid* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int yield_to (struct task_struct*,int) ; 

bool kvm_vcpu_yield_to(struct kvm_vcpu *target)
{
	struct pid *pid;
	struct task_struct *task = NULL;
	bool ret = false;

	rcu_read_lock();
	pid = rcu_dereference(target->pid);
	if (pid)
		task = get_pid_task(target->pid, PIDTYPE_PID);
	rcu_read_unlock();
	if (!task)
		return ret;
	if (task->flags & PF_VCPU) {
		put_task_struct(task);
		return ret;
	}
	ret = yield_to(task, 1);
	put_task_struct(task);

	return ret;
}