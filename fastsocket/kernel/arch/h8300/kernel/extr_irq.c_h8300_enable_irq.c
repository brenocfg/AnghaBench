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
 unsigned int EXT_IRQ0 ; 
 int IER_REGS ; 
 scalar_t__ is_ext_irq (unsigned int) ; 

__attribute__((used)) static void h8300_enable_irq(unsigned int irq)
{
	if (is_ext_irq(irq))
		IER_REGS |= 1 << (irq - EXT_IRQ0);
}