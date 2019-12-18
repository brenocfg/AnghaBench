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
struct TYPE_2__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_PROCPRI ; 
 int /*<<< orphan*/  apic_enabled (struct kvm_lapic*) ; 
 int apic_find_highest_irr (struct kvm_lapic*) ; 
 int apic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_update_ppr (struct kvm_lapic*) ; 

int kvm_apic_has_interrupt(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;
	int highest_irr;

	if (!apic || !apic_enabled(apic))
		return -1;

	apic_update_ppr(apic);
	highest_irr = apic_find_highest_irr(apic);
	if ((highest_irr == -1) ||
	    ((highest_irr & 0xF0) <= apic_get_reg(apic, APIC_PROCPRI)))
		return -1;
	return highest_irr;
}