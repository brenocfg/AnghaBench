#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* action; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  i8259a_startup_irq (int) ; 
 TYPE_2__* irq_desc ; 

__attribute__((used)) static unsigned int
jensen_local_startup(unsigned int irq)
{
	/* the parport is really hw IRQ 1, silly Jensen.  */
	if (irq == 7)
		i8259a_startup_irq(1);
	else
		/*
		 * For all true local interrupts, set the flag that prevents
		 * the IPL from being dropped during handler processing.
		 */
		if (irq_desc[irq].action)
			irq_desc[irq].action->flags |= IRQF_DISABLED;
	return 0;
}