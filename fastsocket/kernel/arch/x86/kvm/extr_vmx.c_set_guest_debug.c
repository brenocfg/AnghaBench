#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long dr7; } ;
struct kvm_vcpu {int guest_debug; TYPE_2__ arch; } ;
struct TYPE_3__ {unsigned long* debugreg; } ;
struct kvm_guest_debug {int control; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_DR7 ; 
 int /*<<< orphan*/  GUEST_RFLAGS ; 
 int KVM_GUESTDBG_ENABLE ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 unsigned long X86_EFLAGS_RF ; 
 unsigned long X86_EFLAGS_TF ; 
 int /*<<< orphan*/  update_exception_bitmap (struct kvm_vcpu*) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int set_guest_debug(struct kvm_vcpu *vcpu, struct kvm_guest_debug *dbg)
{
	int old_debug = vcpu->guest_debug;
	unsigned long flags;

	vcpu->guest_debug = dbg->control;
	if (!(vcpu->guest_debug & KVM_GUESTDBG_ENABLE))
		vcpu->guest_debug = 0;

	if (vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP)
		vmcs_writel(GUEST_DR7, dbg->arch.debugreg[7]);
	else
		vmcs_writel(GUEST_DR7, vcpu->arch.dr7);

	flags = vmcs_readl(GUEST_RFLAGS);
	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		flags |= X86_EFLAGS_TF | X86_EFLAGS_RF;
	else if (old_debug & KVM_GUESTDBG_SINGLESTEP)
		flags &= ~(X86_EFLAGS_TF | X86_EFLAGS_RF);
	vmcs_writel(GUEST_RFLAGS, flags);

	update_exception_bitmap(vcpu);

	return 0;
}