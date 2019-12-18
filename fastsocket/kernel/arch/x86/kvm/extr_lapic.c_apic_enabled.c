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
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
 scalar_t__ apic_hw_enabled (struct kvm_lapic*) ; 
 scalar_t__ apic_sw_enabled (struct kvm_lapic*) ; 

__attribute__((used)) static inline int apic_enabled(struct kvm_lapic *apic)
{
	return apic_sw_enabled(apic) &&	apic_hw_enabled(apic);
}