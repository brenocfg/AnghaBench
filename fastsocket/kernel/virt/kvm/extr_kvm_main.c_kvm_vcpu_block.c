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
struct kvm_vcpu {int /*<<< orphan*/  wq; int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_arch_vcpu_runnable (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_has_pending_timer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  wait ; 

void kvm_vcpu_block(struct kvm_vcpu *vcpu)
{
	DEFINE_WAIT(wait);

	for (;;) {
		prepare_to_wait(&vcpu->wq, &wait, TASK_INTERRUPTIBLE);

		if (kvm_arch_vcpu_runnable(vcpu)) {
			set_bit(KVM_REQ_UNHALT, &vcpu->requests);
			break;
		}
		if (kvm_cpu_has_pending_timer(vcpu))
			break;
		if (signal_pending(current))
			break;

		vcpu_put(vcpu);
		schedule();
		vcpu_load(vcpu);
	}

	finish_wait(&vcpu->wq, &wait);
}