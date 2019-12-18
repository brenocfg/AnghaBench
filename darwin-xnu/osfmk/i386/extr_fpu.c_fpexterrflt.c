#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_2__* thread_t ;
struct x86_fx_thread_state {int fx_control; int const fx_status; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {struct x86_fx_thread_state* ifps; } ;
struct TYPE_6__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_ARITHMETIC ; 
 int /*<<< orphan*/  EXC_I386_EXTERR ; 
 int /*<<< orphan*/  FALSE ; 
 int FPC_DM ; 
 int FPC_IM ; 
 int FPC_OM ; 
 int FPC_PE ; 
 int FPC_UE ; 
 int FPC_ZM ; 
 int const FPS_DE ; 
 int const FPS_IE ; 
 int const FPS_OE ; 
 int const FPS_PE ; 
 int const FPS_UE ; 
 int const FPS_ZE ; 
 scalar_t__ current_task () ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  fp_save (TYPE_2__*) ; 
 int /*<<< orphan*/  fpxlog (int /*<<< orphan*/ ,int const,int,int const) ; 
 scalar_t__ get_interrupt_level () ; 
 int /*<<< orphan*/  i386_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ kernel_task ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
fpexterrflt(void)
{
	thread_t	thr_act = current_thread();
	struct x86_fx_thread_state *ifps = thr_act->machine.ifps;
	boolean_t	intr;

	intr = ml_set_interrupts_enabled(FALSE);

	if (get_interrupt_level())
		panic("FPU error exception at interrupt context\n");
	if (current_task() == kernel_task)
		panic("FPU error exception in kernel thread context\n");

	/*
	 * Save the FPU state and turn off the FPU.
	 */
	fp_save(thr_act);

	(void)ml_set_interrupts_enabled(intr);

	const uint32_t mask = ifps->fx_control &
	    (FPC_IM | FPC_DM | FPC_ZM | FPC_OM | FPC_UE | FPC_PE);
	const uint32_t xcpt = ~mask & (ifps->fx_status &
	    (FPS_IE | FPS_DE | FPS_ZE | FPS_OE | FPS_UE | FPS_PE));
	fpxlog(EXC_I386_EXTERR, ifps->fx_status, ifps->fx_control, xcpt);
	/*
	 * Raise FPU exception.
	 * Locking not needed on pcb->ifps,
	 * since thread is running.
	 */
	i386_exception(EXC_ARITHMETIC,
		       EXC_I386_EXTERR,
		       ifps->fx_status);

	/*NOTREACHED*/
}