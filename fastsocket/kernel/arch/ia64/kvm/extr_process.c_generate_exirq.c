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
typedef  unsigned int uint64_t ;
struct kvm_vcpu {int dummy; } ;
struct kvm_pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned int IA64_PSR_IC ; 
 unsigned int IA64_PSR_RI ; 
 unsigned int VCPU (struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  panic_vm (struct kvm_vcpu*,char*) ; 
 int /*<<< orphan*/  reflect_interruption (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,struct kvm_pt_regs*) ; 
 struct kvm_pt_regs* vcpu_regs (struct kvm_vcpu*) ; 

__attribute__((used)) static void generate_exirq(struct kvm_vcpu *vcpu)
{
	unsigned  vpsr;
	uint64_t isr;

	struct kvm_pt_regs *regs = vcpu_regs(vcpu);

	vpsr = VCPU(vcpu, vpsr);
	isr = vpsr & IA64_PSR_RI;
	if (!(vpsr & IA64_PSR_IC))
		panic_vm(vcpu, "Trying to inject one IRQ with psr.ic=0\n");
	reflect_interruption(0, isr, 0, 12, regs); /* EXT IRQ */
}