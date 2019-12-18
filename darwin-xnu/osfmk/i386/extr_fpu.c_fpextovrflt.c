#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xstate_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct x86_fx_thread_state {int dummy; } ;
typedef  TYPE_1__* pcb_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct x86_fx_thread_state* ifps; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_BAD_ACCESS ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* THREAD_TO_PCB (int /*<<< orphan*/ ) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int /*<<< orphan*/  clear_fpu () ; 
 int /*<<< orphan*/  clear_ts () ; 
 scalar_t__ current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  current_xstate () ; 
 int /*<<< orphan*/  fninit () ; 
 int /*<<< orphan*/  fp_state_free (struct x86_fx_thread_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_interrupt_level () ; 
 int /*<<< orphan*/  i386_exception (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_task ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
fpextovrflt(void)
{
	thread_t	thr_act = current_thread();
	pcb_t		pcb;
	struct x86_fx_thread_state *ifps;
	boolean_t	intr;
	xstate_t	xstate = current_xstate();

	intr = ml_set_interrupts_enabled(FALSE);

	if (get_interrupt_level())
		panic("FPU segment overrun exception  at interrupt context\n");
	if (current_task() == kernel_task)
		panic("FPU segment overrun exception in kernel thread context\n");

	/*
	 * This is a non-recoverable error.
	 * Invalidate the thread`s FPU state.
	 */
	pcb = THREAD_TO_PCB(thr_act);
	simple_lock(&pcb->lock);
	ifps = pcb->ifps;
	pcb->ifps = 0;
	simple_unlock(&pcb->lock);

	/*
	 * Re-initialize the FPU.
	 */
	clear_ts();
	fninit();

	/*
	 * And disable access.
	 */
	clear_fpu();

	(void)ml_set_interrupts_enabled(intr);

	if (ifps)
	    fp_state_free(ifps, xstate);

	/*
	 * Raise exception.
	 */
	i386_exception(EXC_BAD_ACCESS, VM_PROT_READ|VM_PROT_EXECUTE, 0);
	/*NOTREACHED*/
}