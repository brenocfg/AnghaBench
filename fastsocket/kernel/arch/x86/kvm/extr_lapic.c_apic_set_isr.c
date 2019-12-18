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
struct kvm_lapic {scalar_t__ isr_count; int highest_isr_cache; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ APIC_ISR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAX_APIC_VECTOR ; 
 int /*<<< orphan*/  __apic_test_and_set_vector (int,scalar_t__) ; 

__attribute__((used)) static inline void apic_set_isr(int vec, struct kvm_lapic *apic)
{
	if (!__apic_test_and_set_vector(vec, apic->regs + APIC_ISR))
		++apic->isr_count;
	BUG_ON(apic->isr_count > MAX_APIC_VECTOR);
	/*
	 * ISR (in service register) bit is set when injecting an interrupt.
	 * The highest vector is injected. Thus the latest bit set matches
	 * the highest bit in ISR.
	 */
	apic->highest_isr_cache = vec;
}