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
 unsigned int APIC_DM_NMI ; 
 int /*<<< orphan*/  APIC_LVT1 ; 
 unsigned int APIC_LVT_MASKED ; 
 unsigned int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,unsigned int) ; 

void uv_nmi_init(void)
{
	unsigned int value;

	/*
	 * Unmask NMI on all cpus
	 */
	value = apic_read(APIC_LVT1) | APIC_DM_NMI;
	value &= ~APIC_LVT_MASKED;
	apic_write(APIC_LVT1, value);
}