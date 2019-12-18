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
 scalar_t__ LASAT_IRQ_BASE ; 
 int* lasat_int_mask ; 
 int lasat_int_mask_shift ; 

void disable_lasat_irq(unsigned int irq_nr)
{
	irq_nr -= LASAT_IRQ_BASE;
	*lasat_int_mask &= ~(1 << irq_nr) << lasat_int_mask_shift;
}