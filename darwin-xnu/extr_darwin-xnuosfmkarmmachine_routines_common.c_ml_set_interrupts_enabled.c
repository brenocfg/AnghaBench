#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_3__* thread_t ;
typedef  int boolean_t ;
struct TYPE_6__ {TYPE_1__* CpuDatap; } ;
struct TYPE_7__ {TYPE_2__ machine; } ;
struct TYPE_5__ {int cpu_pending_ast; } ;

/* Variables and functions */
 int AST_URGENT ; 
 int DAIFSC_FIQF ; 
 int DAIFSC_IRQF ; 
 int DAIF_IRQF ; 
 int __builtin_arm_rsr (char*) ; 
 int /*<<< orphan*/  __builtin_arm_wsr (char*,int) ; 
 int /*<<< orphan*/  ast_taken_kernel () ; 
 TYPE_3__* current_thread () ; 
 scalar_t__ get_preemption_level () ; 

boolean_t
ml_set_interrupts_enabled(boolean_t enable)
{
	thread_t	thread;
	uint64_t	state;

#if __arm__
#define INTERRUPT_MASK PSR_IRQF
	state = __builtin_arm_rsr("cpsr");
#else
#define INTERRUPT_MASK DAIF_IRQF
	state = __builtin_arm_rsr("DAIF");
#endif
	if (enable && (state & INTERRUPT_MASK)) {
#if INTERRUPT_MASKED_DEBUG
		if (interrupt_masked_debug) {
			// Interrupts are currently masked, we will enable them (after finishing this check)
			thread = current_thread();
			ml_check_interrupts_disabled_duration(thread);
			thread->machine.intmask_timestamp = 0;
		}
#endif	// INTERRUPT_MASKED_DEBUG
		if (get_preemption_level() == 0) {
			thread = current_thread();
			while (thread->machine.CpuDatap->cpu_pending_ast & AST_URGENT) {
#if __ARM_USER_PROTECT__
				uintptr_t up = arm_user_protect_begin(thread);
#endif
				ast_taken_kernel();
#if __ARM_USER_PROTECT__
				arm_user_protect_end(thread, up, FALSE);
#endif
			}
		}
#if __arm__
		__asm__ volatile ("cpsie if" ::: "memory"); // Enable IRQ FIQ
#else
		__builtin_arm_wsr("DAIFClr", (DAIFSC_IRQF | DAIFSC_FIQF));
#endif
	} else if (!enable && ((state & INTERRUPT_MASK) == 0)) {
#if __arm__
		__asm__ volatile ("cpsid if" ::: "memory"); // Mask IRQ FIQ
#else
		__builtin_arm_wsr("DAIFSet", (DAIFSC_IRQF | DAIFSC_FIQF));
#endif
#if INTERRUPT_MASKED_DEBUG
		if (interrupt_masked_debug) {
			// Interrupts were enabled, we just masked them
			current_thread()->machine.intmask_timestamp = mach_absolute_time();
		}
#endif
	}
	return ((state & INTERRUPT_MASK) == 0);
}