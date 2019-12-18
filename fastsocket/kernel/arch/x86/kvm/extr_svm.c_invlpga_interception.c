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
struct TYPE_2__ {int /*<<< orphan*/ * regs; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct vcpu_svm {struct kvm_vcpu vcpu; scalar_t__ next_rip; } ;

/* Variables and functions */
 size_t VCPU_REGS_RAX ; 
 int /*<<< orphan*/  kvm_mmu_invlpg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nsvm_printk (char*) ; 
 int /*<<< orphan*/  skip_emulated_instruction (struct kvm_vcpu*) ; 

__attribute__((used)) static int invlpga_interception(struct vcpu_svm *svm)
{
	struct kvm_vcpu *vcpu = &svm->vcpu;
	nsvm_printk("INVLPGA\n");

	/* Let's treat INVLPGA the same as INVLPG (can be optimized!) */
	kvm_mmu_invlpg(vcpu, vcpu->arch.regs[VCPU_REGS_RAX]);

	svm->next_rip = kvm_rip_read(&svm->vcpu) + 3;
	skip_emulated_instruction(&svm->vcpu);
	return 1;
}