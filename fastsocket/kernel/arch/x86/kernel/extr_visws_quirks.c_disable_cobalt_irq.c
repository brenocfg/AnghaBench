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

/* Variables and functions */
 int /*<<< orphan*/  CO_APIC_LO (int) ; 
 int /*<<< orphan*/  CO_APIC_MASK ; 
 int /*<<< orphan*/  co_apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  co_apic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_co_apic (unsigned int) ; 

__attribute__((used)) static void disable_cobalt_irq(unsigned int irq)
{
	int entry = is_co_apic(irq);

	co_apic_write(CO_APIC_LO(entry), CO_APIC_MASK);
	co_apic_read(CO_APIC_LO(entry));
}