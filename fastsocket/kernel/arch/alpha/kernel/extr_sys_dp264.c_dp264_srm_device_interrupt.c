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
 int /*<<< orphan*/  handle_irq (int) ; 

__attribute__((used)) static void 
dp264_srm_device_interrupt(unsigned long vector)
{
	int irq;

	irq = (vector - 0x800) >> 4;

	/*
	 * The SRM console reports PCI interrupts with a vector calculated by:
	 *
	 *	0x900 + (0x10 * DRIR-bit)
	 *
	 * So bit 16 shows up as IRQ 32, etc.
	 * 
	 * On DP264/BRICK/MONET, we adjust it down by 16 because at least
	 * that many of the low order bits of the DRIR are not used, and
	 * so we don't count them.
	 */
	if (irq >= 32)
		irq -= 16;

	handle_irq(irq);
}