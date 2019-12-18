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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __smp_irq_work_interrupt () ; 
 int /*<<< orphan*/  exiting_irq () ; 
 int /*<<< orphan*/  irq_work_entering_irq () ; 

void smp_irq_work_interrupt(struct pt_regs *regs)
{
	irq_work_entering_irq();
	__smp_irq_work_interrupt();
	exiting_irq();
}