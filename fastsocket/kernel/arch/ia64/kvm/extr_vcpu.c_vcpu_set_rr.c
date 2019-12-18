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
union ia64_rr {unsigned long val; } ;
struct exit_ctl_data {int /*<<< orphan*/  exit_reason; } ;
struct TYPE_2__ {unsigned long* vrr; unsigned long vmm_rr; unsigned long metaphysical_saved_rr4; unsigned long metaphysical_saved_rr0; struct exit_ctl_data exit_data; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_REASON_SWITCH_RR6 ; 
 unsigned long IA64_NO_FAULT ; 
#define  VRN0 130 
#define  VRN4 129 
#define  VRN6 128 
 unsigned long VRN_SHIFT ; 
 int /*<<< orphan*/  ia64_set_rr (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  is_physical_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long vcpu_get_rr (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  vmm_transition (struct kvm_vcpu*) ; 
 unsigned long vrrtomrr (unsigned long) ; 

unsigned long vcpu_set_rr(struct kvm_vcpu *vcpu, unsigned long reg,
					unsigned long val)
{
	union ia64_rr oldrr, newrr;
	unsigned long rrval;
	struct exit_ctl_data *p = &vcpu->arch.exit_data;
	unsigned long psr;

	oldrr.val = vcpu_get_rr(vcpu, reg);
	newrr.val = val;
	vcpu->arch.vrr[reg >> VRN_SHIFT] = val;

	switch ((unsigned long)(reg >> VRN_SHIFT)) {
	case VRN6:
		vcpu->arch.vmm_rr = vrrtomrr(val);
		local_irq_save(psr);
		p->exit_reason = EXIT_REASON_SWITCH_RR6;
		vmm_transition(vcpu);
		local_irq_restore(psr);
		break;
	case VRN4:
		rrval = vrrtomrr(val);
		vcpu->arch.metaphysical_saved_rr4 = rrval;
		if (!is_physical_mode(vcpu))
			ia64_set_rr(reg, rrval);
		break;
	case VRN0:
		rrval = vrrtomrr(val);
		vcpu->arch.metaphysical_saved_rr0 = rrval;
		if (!is_physical_mode(vcpu))
			ia64_set_rr(reg, rrval);
		break;
	default:
		ia64_set_rr(reg, vrrtomrr(val));
		break;
	}

	return (IA64_NO_FAULT);
}