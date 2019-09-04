#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* thread_t ;
typedef  int mach_msg_type_number_t ;
typedef  int mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  exception_type_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_10__ {int /*<<< orphan*/ * upcb; TYPE_3__* DebugData; } ;
struct TYPE_11__ {TYPE_4__ machine; } ;
struct TYPE_7__ {int mdscr_el1; } ;
struct TYPE_8__ {TYPE_1__ ds64; } ;
struct TYPE_9__ {TYPE_2__ uds; } ;

/* Variables and functions */
 int DAIF_FIQF ; 
 int DAIF_IRQF ; 
 int /*<<< orphan*/  EXC_BREAKPOINT ; 
 int /*<<< orphan*/  PSR64_IS_USER (int) ; 
 int PSR64_SS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* current_thread () ; 
 int /*<<< orphan*/  exception_triage (int /*<<< orphan*/ ,int*,int) ; 
 int get_saved_state_cpsr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_with_thread_kernel_state (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_saved_state_cpsr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
handle_sw_step_debug(arm_saved_state_t *state)
{
	thread_t thread = current_thread();
	exception_type_t exc;
	mach_exception_data_type_t codes[2];
	mach_msg_type_number_t numcodes = 2;

	if (!PSR64_IS_USER(get_saved_state_cpsr(state))) {
		panic_with_thread_kernel_state("SW_STEP_DEBUG exception from kernel.", state);
	}

	// Disable single step and unmask interrupts (in the saved state, anticipating next exception return)
	if (thread->machine.DebugData != NULL) {
		thread->machine.DebugData->uds.ds64.mdscr_el1 &= ~0x1;
	} else {
		panic_with_thread_kernel_state("SW_STEP_DEBUG exception thread DebugData is NULL.", state);
	}

	set_saved_state_cpsr((thread->machine.upcb),
	    get_saved_state_cpsr((thread->machine.upcb)) & ~(PSR64_SS | DAIF_IRQF | DAIF_FIQF));

	// Special encoding for gdb single step event on ARM
	exc = EXC_BREAKPOINT;
	codes[0] = 1;
	codes[1] = 0;

	exception_triage(exc, codes, numcodes);
	assert(0); /* NOTREACHED */
}