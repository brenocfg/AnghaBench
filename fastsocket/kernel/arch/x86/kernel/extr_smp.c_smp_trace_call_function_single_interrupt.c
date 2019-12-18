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
 int /*<<< orphan*/  CALL_FUNCTION_SINGLE_VECTOR ; 
 int /*<<< orphan*/  __smp_call_function_single_interrupt () ; 
 int /*<<< orphan*/  exiting_irq () ; 
 int /*<<< orphan*/  smp_entering_irq () ; 
 int /*<<< orphan*/  trace_call_function_single_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_call_function_single_exit (int /*<<< orphan*/ ) ; 

void smp_trace_call_function_single_interrupt(struct pt_regs *regs)
{
	smp_entering_irq();
	trace_call_function_single_entry(CALL_FUNCTION_SINGLE_VECTOR);
	__smp_call_function_single_interrupt();
	trace_call_function_single_exit(CALL_FUNCTION_SINGLE_VECTOR);
	exiting_irq();
}