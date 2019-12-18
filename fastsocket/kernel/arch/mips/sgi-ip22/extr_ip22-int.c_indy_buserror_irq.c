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
 int SGI_BUSERR_IRQ ; 
 int /*<<< orphan*/  ip22_be_interrupt (int) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  irq_to_desc (int) ; 
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void indy_buserror_irq(void)
{
	int irq = SGI_BUSERR_IRQ;

	irq_enter();
	kstat_incr_irqs_this_cpu(irq, irq_to_desc(irq));
	ip22_be_interrupt(irq);
	irq_exit();
}