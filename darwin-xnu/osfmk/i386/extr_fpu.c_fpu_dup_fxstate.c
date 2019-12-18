#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t xstate_t ;
typedef  TYPE_2__* thread_t ;
struct x86_fx_thread_state {int /*<<< orphan*/  fx_MXCSR; scalar_t__ fp_valid; } ;
typedef  TYPE_3__* pcb_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/  lock; struct x86_fx_thread_state* ifps; } ;
struct TYPE_11__ {size_t xstate; struct x86_fx_thread_state* ifps; } ;
struct TYPE_12__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* THREAD_TO_PCB (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_fpu () ; 
 int /*<<< orphan*/  clear_ts () ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  fp_save (TYPE_2__*) ; 
 struct x86_fx_thread_state* fp_state_alloc (size_t) ; 
 int /*<<< orphan*/  fp_state_free (struct x86_fx_thread_state*,size_t) ; 
 int /*<<< orphan*/ * fp_state_size ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcsr_capability_mask ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 size_t thread_xstate (TYPE_2__*) ; 

void
fpu_dup_fxstate(
	thread_t	parent,
	thread_t	child)
{
	struct x86_fx_thread_state *new_ifps = NULL;
	boolean_t	intr;
	pcb_t		ppcb;
	xstate_t	xstate = thread_xstate(parent);

	ppcb = THREAD_TO_PCB(parent);

	if (ppcb->ifps == NULL)
	        return;

        if (child->machine.ifps)
	        panic("fpu_dup_fxstate: child's ifps non-null");

	new_ifps = fp_state_alloc(xstate);

	simple_lock(&ppcb->lock);

	if (ppcb->ifps != NULL) {
		struct x86_fx_thread_state *ifps = ppcb->ifps;
	        /*
		 * Make sure we`ve got the latest fp state info
		 */
		if (current_thread() == parent) {
			intr = ml_set_interrupts_enabled(FALSE);
			assert(current_thread() == parent);
			clear_ts();
			fp_save(parent);
			clear_fpu();

			(void)ml_set_interrupts_enabled(intr);
		}

		if (ifps->fp_valid) {
			child->machine.ifps = new_ifps;
			child->machine.xstate = xstate;
			bcopy((char *)(ppcb->ifps),
			      (char *)(child->machine.ifps),
			      fp_state_size[xstate]);

			/* Mark the new fp saved state as non-live. */
			/* Temporarily disabled: radar 4647827
			 * new_ifps->fp_valid = TRUE;
			 */

			/*
			 * Clear any reserved bits in the MXCSR to prevent a GPF
			 * when issuing an FXRSTOR.
			 */
			new_ifps->fx_MXCSR &= mxcsr_capability_mask;
			new_ifps = NULL;
		}
	}
	simple_unlock(&ppcb->lock);

	if (new_ifps != NULL)
	        fp_state_free(new_ifps, xstate);
}