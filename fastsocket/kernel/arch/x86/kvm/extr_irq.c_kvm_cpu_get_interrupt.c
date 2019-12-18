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
struct TYPE_3__ {int nr; } ;
struct TYPE_4__ {TYPE_1__ interrupt; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;
struct kvm_pic {scalar_t__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_apic_accept_pic_intr (struct kvm_vcpu*) ; 
 int kvm_get_apic_interrupt (struct kvm_vcpu*) ; 
 int kvm_pic_read_irq (int /*<<< orphan*/ ) ; 
 struct kvm_pic* pic_irqchip (int /*<<< orphan*/ ) ; 

int kvm_cpu_get_interrupt(struct kvm_vcpu *v)
{
	struct kvm_pic *s;
	int vector;

	if (!irqchip_in_kernel(v->kvm))
		return v->arch.interrupt.nr;

	vector = kvm_get_apic_interrupt(v);	/* APIC */
	if (vector == -1) {
		if (kvm_apic_accept_pic_intr(v)) {
			s = pic_irqchip(v->kvm);
			s->output = 0;		/* PIC */
			vector = kvm_pic_read_irq(v->kvm);
		}
	}
	return vector;
}