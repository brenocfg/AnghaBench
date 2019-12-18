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
typedef  size_t xstate_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct x86_fx_thread_state {int /*<<< orphan*/  fp_valid; int /*<<< orphan*/  fp_save_layout; } ;
typedef  TYPE_1__* pcb_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {size_t xstate; struct x86_fx_thread_state* ifps; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FXSAVE32 ; 
 int /*<<< orphan*/  FXSAVE64 ; 
 TYPE_1__* THREAD_TO_PCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XSAVE32 ; 
 int /*<<< orphan*/  XSAVE64 ; 
 scalar_t__ __improbable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_ts () ; 
 int /*<<< orphan*/  current_thread () ; 
 size_t current_xstate () ; 
 int /*<<< orphan*/  fp_load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_save (int /*<<< orphan*/ ) ; 
 struct x86_fx_thread_state* fp_state_alloc (size_t) ; 
 int /*<<< orphan*/  fp_state_free (struct x86_fx_thread_state*,size_t) ; 
 int /*<<< orphan*/ * fp_state_size ; 
 int /*<<< orphan*/  fpinit () ; 
 scalar_t__ fpu_YMM_capable ; 
 int /*<<< orphan*/  get_interrupt_level () ; 
 int /*<<< orphan*/  initial_fp_state ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_is_64bit_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_isr_fp_simd_use ; 

void
fpnoextflt(void)
{
	boolean_t	intr;
	thread_t	thr_act;
	pcb_t		pcb;
	struct x86_fx_thread_state *ifps = 0;
	xstate_t	xstate = current_xstate();

	thr_act = current_thread();
	pcb = THREAD_TO_PCB(thr_act);

	if (pcb->ifps == 0 && !get_interrupt_level()) {
	        ifps = fp_state_alloc(xstate);
		bcopy((char *)&initial_fp_state, (char *)ifps,
		    fp_state_size[xstate]);
		if (!thread_is_64bit_addr(thr_act)) {
			ifps->fp_save_layout = fpu_YMM_capable ? XSAVE32 : FXSAVE32;
		}
		else
			ifps->fp_save_layout = fpu_YMM_capable ? XSAVE64 : FXSAVE64;
		ifps->fp_valid = TRUE;
	}
	intr = ml_set_interrupts_enabled(FALSE);

	clear_ts();			/*  Enable FPU use */

	if (__improbable(get_interrupt_level())) {
		/* Track number of #DNA traps at interrupt context,
		 * which is likely suboptimal. Racy, but good enough.
		 */
		x86_isr_fp_simd_use++;
		/*
		 * Save current FP/SIMD context if valid
		 * Initialize live FP/SIMD registers
		 */
		if (pcb->ifps) {
			fp_save(thr_act);
		}
		fpinit();
	} else {
	        if (pcb->ifps == 0) {
		        pcb->ifps = ifps;
		        pcb->xstate = xstate;
			ifps = 0;
		}
		/*
		 * Load this thread`s state into coprocessor live context.
		 */
		fp_load(thr_act);
	}
	(void)ml_set_interrupts_enabled(intr);

	if (ifps)
	        fp_state_free(ifps, xstate);
}