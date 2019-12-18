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
#define  PPC_MSG_CALL_FUNCTION 131 
#define  PPC_MSG_CALL_FUNC_SINGLE 130 
#define  PPC_MSG_DEBUGGER_BREAK 129 
#define  PPC_MSG_RESCHEDULE 128 
 int /*<<< orphan*/  crash_ipi_function_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugger_ipi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/  generic_smp_call_function_single_interrupt () ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void smp_message_recv(int msg)
{
	switch(msg) {
	case PPC_MSG_CALL_FUNCTION:
		generic_smp_call_function_interrupt();
		break;
	case PPC_MSG_RESCHEDULE:
		/* we notice need_resched on exit */
		scheduler_ipi();
		break;
	case PPC_MSG_CALL_FUNC_SINGLE:
		generic_smp_call_function_single_interrupt();
		break;
	case PPC_MSG_DEBUGGER_BREAK:
		if (crash_ipi_function_ptr) {
			crash_ipi_function_ptr(get_irq_regs());
			break;
		}
#ifdef CONFIG_DEBUGGER
		debugger_ipi(get_irq_regs());
		break;
#endif /* CONFIG_DEBUGGER */
		/* FALLTHROUGH */
	default:
		printk("SMP %d: smp_message_recv(): unknown msg %d\n",
		       smp_processor_id(), msg);
		break;
	}
}