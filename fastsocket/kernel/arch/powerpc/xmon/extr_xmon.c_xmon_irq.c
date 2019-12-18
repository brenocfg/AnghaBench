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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  xmon (int /*<<< orphan*/ ) ; 

irqreturn_t xmon_irq(int irq, void *d)
{
	unsigned long flags;
	local_irq_save(flags);
	printf("Keyboard interrupt\n");
	xmon(get_irq_regs());
	local_irq_restore(flags);
	return IRQ_HANDLED;
}