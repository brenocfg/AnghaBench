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
struct kvm_vcpu {int dummy; } ;
struct kvm_pt_regs {unsigned long cr_ifs; void* cr_iip; } ;

/* Variables and functions */
 unsigned long IA64_PSR_BN ; 
 void* VCPU (struct kvm_vcpu*,unsigned long) ; 
 unsigned long iip ; 
 unsigned long ipsr ; 
 int /*<<< orphan*/  vcpu_bsw0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_bsw1 (struct kvm_vcpu*) ; 
 struct kvm_pt_regs* vcpu_regs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_set_psr (struct kvm_vcpu*,unsigned long) ; 

void vcpu_rfi(struct kvm_vcpu *vcpu)
{
	unsigned long ifs, psr;
	struct kvm_pt_regs *regs = vcpu_regs(vcpu);

	psr = VCPU(vcpu, ipsr);
	if (psr & IA64_PSR_BN)
		vcpu_bsw1(vcpu);
	else
		vcpu_bsw0(vcpu);
	vcpu_set_psr(vcpu, psr);
	ifs = VCPU(vcpu, ifs);
	if (ifs >> 63)
		regs->cr_ifs = ifs;
	regs->cr_iip = VCPU(vcpu, iip);
}