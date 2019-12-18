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
struct kvm_vcpu {TYPE_1__* run; int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {scalar_t__ request_interrupt_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_arch_interrupt_allowed (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_cpu_has_interrupt (struct kvm_vcpu*) ; 

__attribute__((used)) static int dm_request_for_irq_injection(struct kvm_vcpu *vcpu)
{
	return (!irqchip_in_kernel(vcpu->kvm) && !kvm_cpu_has_interrupt(vcpu) &&
		vcpu->run->request_interrupt_window &&
		kvm_arch_interrupt_allowed(vcpu));
}