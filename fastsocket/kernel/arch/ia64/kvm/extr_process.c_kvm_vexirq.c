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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_pt_regs {int dummy; } ;

/* Variables and functions */
 int IA64_PSR_RI ; 
 int VCPU (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  reflect_interruption (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct kvm_pt_regs*) ; 
 struct kvm_pt_regs* vcpu_regs (struct kvm_vcpu*) ; 

void kvm_vexirq(struct kvm_vcpu *vcpu)
{
	u64 vpsr, isr;
	struct kvm_pt_regs *regs;

	regs = vcpu_regs(vcpu);
	vpsr = VCPU(vcpu, vpsr);
	isr = vpsr & IA64_PSR_RI;
	reflect_interruption(0, isr, 0, 12, regs); /*EXT IRQ*/
}