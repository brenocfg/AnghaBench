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
 int CO_APIC (unsigned int) ; 
 int CO_APIC_CPU ; 
 int CO_APIC_IDE1 ; 
#define  CO_IRQ_IDE0 129 
#define  CO_IRQ_IDE1 128 
 scalar_t__ IS_CO_APIC (unsigned int) ; 
 int co_apic_ide0_hack () ; 

__attribute__((used)) static int is_co_apic(unsigned int irq)
{
	if (IS_CO_APIC(irq))
		return CO_APIC(irq);

	switch (irq) {
		case 0: return CO_APIC_CPU;
		case CO_IRQ_IDE0: return co_apic_ide0_hack();
		case CO_IRQ_IDE1: return CO_APIC_IDE1;
		default: return -1;
	}
}