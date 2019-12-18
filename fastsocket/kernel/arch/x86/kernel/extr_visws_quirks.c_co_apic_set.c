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
 int /*<<< orphan*/  CO_APIC_HI (int) ; 
 int CO_APIC_LEVEL ; 
 int /*<<< orphan*/  CO_APIC_LO (int) ; 
 int FIRST_EXTERNAL_VECTOR ; 
 int /*<<< orphan*/  co_apic_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void co_apic_set(int entry, int irq)
{
	co_apic_write(CO_APIC_LO(entry), CO_APIC_LEVEL | (irq + FIRST_EXTERNAL_VECTOR));
	co_apic_write(CO_APIC_HI(entry), 0);
}