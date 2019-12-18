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
 unsigned int MARVEL_IRQ_VEC_IRQ_MASK ; 
 unsigned int MARVEL_IRQ_VEC_PE_SHIFT ; 
 int /*<<< orphan*/  handle_irq (unsigned int) ; 

__attribute__((used)) static void 
io7_device_interrupt(unsigned long vector)
{
	unsigned int pid;
	unsigned int irq;

	/*
	 * Vector is 0x800 + (interrupt)
	 *
	 * where (interrupt) is:
	 *
	 *	...16|15 14|13     4|3 0
	 *	-----+-----+--------+---
	 *	  PE |  0  |   irq  | 0
	 *
	 * where (irq) is 
	 *
	 *       0x0800 - 0x0ff0	 - 0x0800 + (LSI id << 4)
	 *	 0x1000 - 0x2ff0	 - 0x1000 + (MSI_DAT<8:0> << 4)
	 */
	pid = vector >> 16;
	irq = ((vector & 0xffff) - 0x800) >> 4;

	irq += 16;				/* offset for legacy */
	irq &= MARVEL_IRQ_VEC_IRQ_MASK;		/* not too many bits */
	irq |= pid << MARVEL_IRQ_VEC_PE_SHIFT;	/* merge the pid     */

	handle_irq(irq);
}