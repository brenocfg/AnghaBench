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
struct kvm_pt_regs {int cr_iip; int /*<<< orphan*/  cr_ipsr; } ;
struct ia64_psr {int ri; } ;

/* Variables and functions */
 struct kvm_pt_regs* vcpu_regs (struct kvm_vcpu*) ; 

void vcpu_decrement_iip(struct kvm_vcpu *vcpu)
{
	struct kvm_pt_regs *regs = vcpu_regs(vcpu);
	struct ia64_psr *ipsr = (struct ia64_psr *)&regs->cr_ipsr;

	if (ipsr->ri == 0) {
		ipsr->ri = 2;
		regs->cr_iip -= 16;
	} else
		ipsr->ri--;
}