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
struct TYPE_2__ {int* gpr; int shadow_pid; int ivpr; scalar_t__ msr; scalar_t__ pc; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int kvmppc_core_vcpu_setup (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_init_timing_stats (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
{
	vcpu->arch.pc = 0;
	vcpu->arch.msr = 0;
	vcpu->arch.gpr[1] = (16<<20) - 8; /* -8 for the callee-save LR slot */

	vcpu->arch.shadow_pid = 1;

	/* Eye-catching number so we know if the guest takes an interrupt
	 * before it's programmed its own IVPR. */
	vcpu->arch.ivpr = 0x55550000;

	kvmppc_init_timing_stats(vcpu);

	return kvmppc_core_vcpu_setup(vcpu);
}