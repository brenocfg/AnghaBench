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
struct TYPE_2__ {scalar_t__ dcr_needed; int /*<<< orphan*/  dcr_is_write; } ;
struct kvm_vcpu {scalar_t__ sigset_active; TYPE_1__ arch; scalar_t__ mmio_needed; int /*<<< orphan*/  mmio_is_write; int /*<<< orphan*/  sigset; } ;
struct kvm_run {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int __kvmppc_vcpu_run (struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_guest_enter () ; 
 int /*<<< orphan*/  kvm_guest_exit () ; 
 int /*<<< orphan*/  kvmppc_complete_dcr_load (struct kvm_vcpu*,struct kvm_run*) ; 
 int /*<<< orphan*/  kvmppc_complete_mmio_load (struct kvm_vcpu*,struct kvm_run*) ; 
 int /*<<< orphan*/  kvmppc_core_deliver_interrupts (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	int r;
	sigset_t sigsaved;

	vcpu_load(vcpu);

	if (vcpu->sigset_active)
		sigprocmask(SIG_SETMASK, &vcpu->sigset, &sigsaved);

	if (vcpu->mmio_needed) {
		if (!vcpu->mmio_is_write)
			kvmppc_complete_mmio_load(vcpu, run);
		vcpu->mmio_needed = 0;
	} else if (vcpu->arch.dcr_needed) {
		if (!vcpu->arch.dcr_is_write)
			kvmppc_complete_dcr_load(vcpu, run);
		vcpu->arch.dcr_needed = 0;
	}

	kvmppc_core_deliver_interrupts(vcpu);

	local_irq_disable();
	kvm_guest_enter();
	r = __kvmppc_vcpu_run(run, vcpu);
	kvm_guest_exit();
	local_irq_enable();

	if (vcpu->sigset_active)
		sigprocmask(SIG_SETMASK, &sigsaved, NULL);

	vcpu_put(vcpu);

	return r;
}