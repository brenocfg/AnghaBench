#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* apic; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;
struct TYPE_6__ {scalar_t__ regs_page; TYPE_1__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 

void kvm_free_lapic(struct kvm_vcpu *vcpu)
{
	if (!vcpu->arch.apic)
		return;

	hrtimer_cancel(&vcpu->arch.apic->lapic_timer.timer);

	if (vcpu->arch.apic->regs_page)
		__free_page(vcpu->arch.apic->regs_page);

	kfree(vcpu->arch.apic);
}