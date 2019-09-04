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
struct TYPE_7__ {int /*<<< orphan*/  fpu_fcw; } ;
typedef  TYPE_1__ x86_float_state64_t ;
struct TYPE_8__ {int /*<<< orphan*/  fpu_ymmh0; } ;
typedef  TYPE_2__ x86_avx_state64_t ;
struct TYPE_9__ {int /*<<< orphan*/  fpu_ymmh0; int /*<<< orphan*/  fpu_zmmh0; int /*<<< orphan*/  fpu_zmm16; int /*<<< orphan*/  fpu_k0; } ;
typedef  TYPE_3__ x86_avx512_state64_t ;
struct TYPE_10__ {int /*<<< orphan*/  fpu_ymmh0; int /*<<< orphan*/  fpu_zmmh0; int /*<<< orphan*/  fpu_k0; } ;
typedef  TYPE_4__ x86_avx512_state32_t ;
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ thread_state_t ;
typedef  scalar_t__ thread_flavor_t ;
struct x86_fx_thread_state {scalar_t__ fp_valid; } ;
struct x86_avx_thread_state {int /*<<< orphan*/  x_YMM_Hi128; } ;
struct x86_avx512_thread_state {int /*<<< orphan*/  x_YMM_Hi128; int /*<<< orphan*/  x_ZMM_Hi256; int /*<<< orphan*/  x_Hi16_ZMM; int /*<<< orphan*/  x_Opmask; } ;
typedef  TYPE_5__* pcb_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  _STRUCT_ZMM_REG ;
typedef  int /*<<< orphan*/  _STRUCT_YMM_REG ;
typedef  int /*<<< orphan*/  _STRUCT_XMM_REG ;
typedef  int /*<<< orphan*/  _STRUCT_OPMASK_REG ;
struct TYPE_11__ {int /*<<< orphan*/  lock; struct x86_fx_thread_state* ifps; } ;

/* Variables and functions */
#define  AVX 135 
#define  AVX512 134 
 int /*<<< orphan*/  DBG_AVX512_STATE (struct x86_avx512_thread_state*) ; 
 int /*<<< orphan*/  FALSE ; 
#define  FP 133 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ THREAD_NULL ; 
 TYPE_5__* THREAD_TO_PCB (scalar_t__) ; 
#define  UNDEFINED 132 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy_nochk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_fpu () ; 
 int /*<<< orphan*/  clear_ts () ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  fp_save (scalar_t__) ; 
 int /*<<< orphan*/ * fp_state_size ; 
 scalar_t__ fpu_capability ; 
 int /*<<< orphan*/  initial_fp_state ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int thread_xstate (scalar_t__) ; 
#define  x86_AVX512_STATE32 131 
#define  x86_AVX512_STATE64 130 
#define  x86_AVX_STATE32 129 
#define  x86_AVX_STATE64 128 

kern_return_t
fpu_get_fxstate(
	thread_t	thr_act,
	thread_state_t	tstate,
	thread_flavor_t f)
{
	struct x86_fx_thread_state	*ifps;
	x86_float_state64_t		*state;
	kern_return_t			ret = KERN_FAILURE;
	pcb_t				pcb;

	if (fpu_capability == UNDEFINED)
		return KERN_FAILURE;

	if ((f == x86_AVX_STATE32 || f == x86_AVX_STATE64) &&
	    fpu_capability < AVX)
		return KERN_FAILURE;

#if !defined(RC_HIDE_XNU_J137)
	if ((f == x86_AVX512_STATE32 || f == x86_AVX512_STATE64) &&
	    thread_xstate(thr_act) != AVX512)
		return KERN_FAILURE;
#endif

	state = (x86_float_state64_t *)tstate;

	assert(thr_act != THREAD_NULL);
	pcb = THREAD_TO_PCB(thr_act);

	simple_lock(&pcb->lock);

	ifps = pcb->ifps;
	if (ifps == 0) {
		/*
		 * No valid floating-point state.
		 */

		bcopy((char *)&initial_fp_state, (char *)&state->fpu_fcw,
		    fp_state_size[FP]);

		simple_unlock(&pcb->lock);

		return KERN_SUCCESS;
	}
	/*
	 * Make sure we`ve got the latest fp state info
	 * If the live fpu state belongs to our target
	 */
	if (thr_act == current_thread()) {
		boolean_t	intr;

		intr = ml_set_interrupts_enabled(FALSE);

		clear_ts();
		fp_save(thr_act);
		clear_fpu();

		(void)ml_set_interrupts_enabled(intr);
	}
	if (ifps->fp_valid) {
        	bcopy((char *)ifps, (char *)&state->fpu_fcw, fp_state_size[FP]);
		switch (thread_xstate(thr_act)) {
		    case UNDEFINED:
			panic("fpu_get_fxstate() UNDEFINED xstate");
			break;
		    case FP:
			break;			/* already done */
		    case AVX: {
			struct x86_avx_thread_state *iavx = (void *) ifps;
			x86_avx_state64_t *xs = (x86_avx_state64_t *) state;
			if (f == x86_AVX_STATE32) {
				bcopy_nochk(iavx->x_YMM_Hi128, &xs->fpu_ymmh0, 8 * sizeof(_STRUCT_XMM_REG));
			} else if (f == x86_AVX_STATE64) {
				bcopy_nochk(iavx->x_YMM_Hi128, &xs->fpu_ymmh0, 16 * sizeof(_STRUCT_XMM_REG));
			}
			break;
		    }
#if !defined(RC_HIDE_XNU_J137)
		    case AVX512: {
			struct x86_avx512_thread_state *iavx = (void *) ifps;
			union {
				thread_state_t       ts;
				x86_avx512_state32_t *s32;
				x86_avx512_state64_t *s64;
			} xs = { .ts = tstate };
			switch (f) {
			    case x86_AVX512_STATE32:
				bcopy_nochk(iavx->x_Opmask,    &xs.s32->fpu_k0,    8 * sizeof(_STRUCT_OPMASK_REG));
				bcopy_nochk(iavx->x_ZMM_Hi256, &xs.s32->fpu_zmmh0, 8 * sizeof(_STRUCT_YMM_REG));
				bcopy_nochk(iavx->x_YMM_Hi128, &xs.s32->fpu_ymmh0, 8 * sizeof(_STRUCT_XMM_REG));
				DBG_AVX512_STATE(iavx);
				break;
			    case x86_AVX_STATE32:
				bcopy_nochk(iavx->x_YMM_Hi128, &xs.s32->fpu_ymmh0, 8 * sizeof(_STRUCT_XMM_REG));
				break;
			    case x86_AVX512_STATE64:
				bcopy_nochk(iavx->x_Opmask,    &xs.s64->fpu_k0,    8 * sizeof(_STRUCT_OPMASK_REG));
				bcopy_nochk(iavx->x_Hi16_ZMM,  &xs.s64->fpu_zmm16, 16 * sizeof(_STRUCT_ZMM_REG));
				bcopy_nochk(iavx->x_ZMM_Hi256, &xs.s64->fpu_zmmh0, 16 * sizeof(_STRUCT_YMM_REG));
				bcopy_nochk(iavx->x_YMM_Hi128, &xs.s64->fpu_ymmh0, 16 * sizeof(_STRUCT_XMM_REG));
				DBG_AVX512_STATE(iavx);
				break;
			    case x86_AVX_STATE64:
				bcopy_nochk(iavx->x_YMM_Hi128, &xs.s64->fpu_ymmh0, 16 * sizeof(_STRUCT_XMM_REG));
				break;
			}
			break;
		    }
#endif
		}

		ret = KERN_SUCCESS;
	}
	simple_unlock(&pcb->lock);

	return ret;
}