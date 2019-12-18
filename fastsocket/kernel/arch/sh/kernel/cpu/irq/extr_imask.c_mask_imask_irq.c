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
 unsigned int IMASK_PRIORITY ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imask_mask ; 
 unsigned int interrupt_priority ; 
 int /*<<< orphan*/  set_interrupt_registers (unsigned int) ; 

__attribute__((used)) static void mask_imask_irq(unsigned int irq)
{
	clear_bit(irq, imask_mask);
	if (interrupt_priority < IMASK_PRIORITY - irq)
		interrupt_priority = IMASK_PRIORITY - irq;
	set_interrupt_registers(interrupt_priority);
}