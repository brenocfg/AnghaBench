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
typedef  scalar_t__ thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  fp_valid; } ;
struct x86_avx_thread_state {TYPE_1__ fp; } ;
struct x86_avx512_thread_state {TYPE_1__ fp; } ;
typedef  TYPE_2__* pcb_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {size_t cpu_xstate; } ;
struct TYPE_6__ {size_t xstate; int /*<<< orphan*/  lock; struct x86_avx_thread_state* ifps; } ;

/* Variables and functions */
 size_t AVX ; 
 size_t AVX512 ; 
 int /*<<< orphan*/  AVX512_XMASK ; 
 int /*<<< orphan*/  DBG (char*,scalar_t__) ; 
 scalar_t__ FALSE ; 
 TYPE_2__* THREAD_TO_PCB (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct x86_avx_thread_state*,struct x86_avx_thread_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_fpu () ; 
 int /*<<< orphan*/  clear_ts () ; 
 TYPE_3__* current_cpu_datap () ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  fp_save (scalar_t__) ; 
 struct x86_avx_thread_state* fp_state_alloc (size_t) ; 
 int /*<<< orphan*/  fp_state_free (struct x86_avx_thread_state*,size_t) ; 
 int /*<<< orphan*/ * fp_state_size ; 
 int /*<<< orphan*/  fpnoextflt () ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsetbv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fpu_savearea_promote_avx512(thread_t thread)
{
	struct x86_avx_thread_state	*ifps = NULL;
	struct x86_avx512_thread_state	*ifps512 = NULL;
	pcb_t				pcb = THREAD_TO_PCB(thread);
	boolean_t			do_avx512_alloc = FALSE;

	DBG("fpu_upgrade_savearea(%p)\n", thread);

	simple_lock(&pcb->lock);

	ifps = pcb->ifps;
	if (ifps == NULL) {
		pcb->xstate = AVX512;
		simple_unlock(&pcb->lock);
		if (thread != current_thread()) {
			/* nothing to be done */

			return;
		}
		fpnoextflt();
		return;
	}

	if (pcb->xstate != AVX512) {
		do_avx512_alloc = TRUE;
	}
	simple_unlock(&pcb->lock);

	if (do_avx512_alloc == TRUE) {
		ifps512 = fp_state_alloc(AVX512);
	}

	simple_lock(&pcb->lock);
	if (thread == current_thread()) {
		boolean_t	intr;

		intr = ml_set_interrupts_enabled(FALSE);

		clear_ts();
		fp_save(thread);
		clear_fpu();

		xsetbv(0, AVX512_XMASK);
		current_cpu_datap()->cpu_xstate = AVX512;
		(void)ml_set_interrupts_enabled(intr);
	}
	assert(ifps->fp.fp_valid);

	/* Allocate an AVX512 savearea and copy AVX state into it */
	if (pcb->xstate != AVX512) {
		bcopy(ifps, ifps512, fp_state_size[AVX]);
		pcb->ifps = ifps512;
		pcb->xstate = AVX512;
		ifps512 = NULL;
	} else {
		ifps = NULL;
	}
	/* The PCB lock is redundant in some scenarios given the higher level
	 * thread mutex, but its pre-emption disablement is relied upon here
	 */
	simple_unlock(&pcb->lock);

	if (ifps) {
		fp_state_free(ifps, AVX);
	}
	if (ifps512) {
		fp_state_free(ifps, AVX512);
	}
}