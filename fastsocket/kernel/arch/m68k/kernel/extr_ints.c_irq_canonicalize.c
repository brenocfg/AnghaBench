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
 scalar_t__ MACH_IS_Q40 ; 

unsigned int irq_canonicalize(unsigned int irq)
{
#ifdef CONFIG_Q40
	if (MACH_IS_Q40 && irq == 11)
		irq = 10;
#endif
	return irq;
}