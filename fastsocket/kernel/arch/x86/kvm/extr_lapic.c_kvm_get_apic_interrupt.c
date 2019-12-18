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
 int /*<<< orphan*/  apic_clear_irr (int,struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_set_isr (int,struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_update_ppr (struct kvm_lapic*) ; 
 int kvm_apic_has_interrupt (struct kvm_vcpu*) ; 

int kvm_get_apic_interrupt(struct kvm_vcpu *vcpu)
{
	int vector = kvm_apic_has_interrupt(vcpu);
	struct kvm_lapic *apic = vcpu->arch.apic;

	if (vector == -1)
		return -1;

	apic_set_isr(vector, apic);
	apic_update_ppr(apic);
	apic_clear_irr(vector, apic);
	return vector;
}