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
 unsigned long EIEM_MASK (unsigned int) ; 
 unsigned long cpu_eiem ; 

__attribute__((used)) static void cpu_disable_irq(unsigned int irq)
{
	unsigned long eirr_bit = EIEM_MASK(irq);

	cpu_eiem &= ~eirr_bit;
	/* Do nothing on the other CPUs.  If they get this interrupt,
	 * The & cpu_eiem in the do_cpu_irq_mask() ensures they won't
	 * handle it, and the set_eiem() at the bottom will ensure it
	 * then gets disabled */
}