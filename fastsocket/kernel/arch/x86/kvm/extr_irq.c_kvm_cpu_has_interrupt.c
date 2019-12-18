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
struct TYPE_3__ {int pending; } ;
struct TYPE_4__ {TYPE_1__ interrupt; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;
struct kvm_pic {int output; } ;

/* Variables and functions */
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_apic_accept_pic_intr (struct kvm_vcpu*) ; 
 int kvm_apic_has_interrupt (struct kvm_vcpu*) ; 
 struct kvm_pic* pic_irqchip (int /*<<< orphan*/ ) ; 

int kvm_cpu_has_interrupt(struct kvm_vcpu *v)
{
	struct kvm_pic *s;

	if (!irqchip_in_kernel(v->kvm))
		return v->arch.interrupt.pending;

	if (kvm_apic_has_interrupt(v) == -1) {	/* LAPIC */
		if (kvm_apic_accept_pic_intr(v)) {
			s = pic_irqchip(v->kvm);	/* PIC */
			return s->output;
		} else
			return 0;
	}
	return 1;
}