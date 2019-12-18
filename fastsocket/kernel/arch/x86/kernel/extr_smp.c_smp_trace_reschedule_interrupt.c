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
 int /*<<< orphan*/  RESCHEDULE_VECTOR ; 
 int /*<<< orphan*/  __smp_reschedule_interrupt () ; 
 int /*<<< orphan*/  exiting_irq () ; 
 int /*<<< orphan*/  smp_entering_irq () ; 
 int /*<<< orphan*/  trace_reschedule_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_reschedule_exit (int /*<<< orphan*/ ) ; 

void smp_trace_reschedule_interrupt(struct pt_regs *regs)
{
	/*
	 * Need to call irq_enter() before calling the trace point.
	 * __smp_reschedule_interrupt() calls irq_enter/exit() too (in
	 * scheduler_ipi(). This is OK, since those functions are allowed
	 * to nest.
	 */
	smp_entering_irq();
	trace_reschedule_entry(RESCHEDULE_VECTOR);
	__smp_reschedule_interrupt();
	trace_reschedule_exit(RESCHEDULE_VECTOR);
	exiting_irq();
	/*
	 * KVM uses this interrupt to force a cpu out of guest mode
	 */
}