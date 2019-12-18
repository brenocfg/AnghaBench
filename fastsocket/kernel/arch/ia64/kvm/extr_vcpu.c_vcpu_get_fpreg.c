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
struct kvm_pt_regs {int dummy; } ;
struct ia64_fpreg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  getfpreg (unsigned long,struct ia64_fpreg*,struct kvm_pt_regs*) ; 
 struct kvm_pt_regs* vcpu_regs (struct kvm_vcpu*) ; 

void vcpu_get_fpreg(struct kvm_vcpu *vcpu, unsigned long reg,
						struct ia64_fpreg *val)
{
	struct kvm_pt_regs *regs = vcpu_regs(vcpu);

	getfpreg(reg, val, regs);   /* FIXME: handle NATs later*/
}