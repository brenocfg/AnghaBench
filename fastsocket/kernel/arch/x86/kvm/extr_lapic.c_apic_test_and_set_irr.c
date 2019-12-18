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
struct kvm_lapic {int irr_pending; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ APIC_IRR ; 
 int apic_test_and_set_vector (int,scalar_t__) ; 

__attribute__((used)) static inline int apic_test_and_set_irr(int vec, struct kvm_lapic *apic)
{
	apic->irr_pending = true;
	return apic_test_and_set_vector(vec, apic->regs + APIC_IRR);
}