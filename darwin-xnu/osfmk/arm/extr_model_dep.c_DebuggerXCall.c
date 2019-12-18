#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  cpsr; } ;
typedef  TYPE_2__ arm_saved_state_t ;
struct TYPE_9__ {scalar_t__ kstackptr; } ;
struct TYPE_11__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMB_ISH ; 
 scalar_t__ FALSE ; 
 scalar_t__ PSR64_IS_KERNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ PSR_IS_KERNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __builtin_arm_dmb (int /*<<< orphan*/ ) ; 
 TYPE_8__* current_thread () ; 
 int /*<<< orphan*/  debugger_sync ; 
 int /*<<< orphan*/  get_saved_state_cpsr (TYPE_2__*) ; 
 int /*<<< orphan*/  hw_atomic_sub (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mp_kdp_trap ; 
 int /*<<< orphan*/  set_saved_state_fp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_saved_state_lr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_saved_state_pc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_saved_state_sp (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
DebuggerXCall(
	void		*ctx)
{
	boolean_t		save_context = FALSE;
	vm_offset_t		kstackptr = 0;
	arm_saved_state_t	*regs = (arm_saved_state_t *) ctx;

	if (regs != NULL) {
#if defined(__arm64__)
		save_context = PSR64_IS_KERNEL(get_saved_state_cpsr(regs));
#else
		save_context = PSR_IS_KERNEL(regs->cpsr);
#endif
	}

	kstackptr = current_thread()->machine.kstackptr;
	arm_saved_state_t *state = (arm_saved_state_t *)kstackptr;

	if (save_context) {
		/* Save the interrupted context before acknowledging the signal */
		*state = *regs;

	} else if (regs) {
		/* zero old state so machine_trace_thread knows not to backtrace it */
		set_saved_state_fp(state, 0);
		set_saved_state_pc(state, 0);
		set_saved_state_lr(state, 0);
		set_saved_state_sp(state, 0);
	}

	(void)hw_atomic_sub(&debugger_sync, 1);
	__builtin_arm_dmb(DMB_ISH);
	while (mp_kdp_trap);

	/* Any cleanup for our pushed context should go here */
}