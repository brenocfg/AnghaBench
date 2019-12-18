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
struct kvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ cpu_has_vmx_virtualize_apic_accesses () ; 
 scalar_t__ flexpriority_enabled ; 
 scalar_t__ irqchip_in_kernel (struct kvm*) ; 

__attribute__((used)) static inline int vm_need_virtualize_apic_accesses(struct kvm *kvm)
{
	return flexpriority_enabled &&
		(cpu_has_vmx_virtualize_apic_accesses()) &&
		(irqchip_in_kernel(kvm));
}