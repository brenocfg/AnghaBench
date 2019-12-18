#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pid {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  preempt_notifier; struct pid* pid; int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__* pids; } ;
struct TYPE_4__ {struct pid* pid; } ;

/* Variables and functions */
 size_t PIDTYPE_PID ; 
 TYPE_2__* current ; 
 int get_cpu () ; 
 struct pid* get_task_pid (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_load (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_notifier_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct pid*,struct pid*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ unlikely (int) ; 

void vcpu_load(struct kvm_vcpu *vcpu)
{
	int cpu;

	mutex_lock(&vcpu->mutex);
	if (unlikely(vcpu->pid != current->pids[PIDTYPE_PID].pid)) {
		/* The thread running this VCPU changed. */
		struct pid *oldpid = vcpu->pid;
		struct pid *newpid = get_task_pid(current, PIDTYPE_PID);
		rcu_assign_pointer(vcpu->pid, newpid);
		synchronize_rcu();
		put_pid(oldpid);
	}
	cpu = get_cpu();
	preempt_notifier_register(&vcpu->preempt_notifier);
	kvm_arch_vcpu_load(vcpu, cpu);
	put_cpu();
}