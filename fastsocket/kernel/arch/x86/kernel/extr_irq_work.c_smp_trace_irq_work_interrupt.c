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
 int /*<<< orphan*/  IRQ_WORK_VECTOR ; 
 int /*<<< orphan*/  __smp_irq_work_interrupt () ; 
 int /*<<< orphan*/  exiting_irq () ; 
 int /*<<< orphan*/  irq_work_entering_irq () ; 
 int /*<<< orphan*/  trace_irq_work_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_irq_work_exit (int /*<<< orphan*/ ) ; 

void smp_trace_irq_work_interrupt(struct pt_regs *regs)
{
	irq_work_entering_irq();
	trace_irq_work_entry(IRQ_WORK_VECTOR);
	__smp_irq_work_interrupt();
	trace_irq_work_exit(IRQ_WORK_VECTOR);
	exiting_irq();
}