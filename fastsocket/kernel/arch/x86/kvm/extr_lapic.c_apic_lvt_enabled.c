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
 int APIC_LVT_MASKED ; 
 int apic_get_reg (struct kvm_lapic*,int) ; 

__attribute__((used)) static inline int apic_lvt_enabled(struct kvm_lapic *apic, int lvt_type)
{
	return !(apic_get_reg(apic, lvt_type) & APIC_LVT_MASKED);
}