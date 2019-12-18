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
struct kvm_lapic {int highest_isr_cache; scalar_t__ regs; int /*<<< orphan*/  isr_count; } ;

/* Variables and functions */
 scalar_t__ APIC_ISR ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int find_highest_vector (scalar_t__) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int apic_find_highest_isr(struct kvm_lapic *apic)
{
	int result;
	if (!apic->isr_count)
		return -1;
	if (likely(apic->highest_isr_cache != -1))
		return apic->highest_isr_cache;

	result = find_highest_vector(apic->regs + APIC_ISR);
	ASSERT(result == -1 || result >= 16);

	return result;
}