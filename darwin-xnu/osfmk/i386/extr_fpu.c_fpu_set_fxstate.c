#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  fpu_fcw; int /*<<< orphan*/  fpu_mxcsr; } ;
typedef  TYPE_5__ x86_float_state64_t ;
struct TYPE_16__ {int /*<<< orphan*/  fpu_ymmh0; } ;
typedef  TYPE_6__ x86_avx_state64_t ;
struct TYPE_17__ {int /*<<< orphan*/  fpu_ymmh0; int /*<<< orphan*/  fpu_zmmh0; int /*<<< orphan*/  fpu_zmm16; int /*<<< orphan*/  fpu_k0; } ;
typedef  TYPE_7__ x86_avx512_state64_t ;
struct TYPE_18__ {int /*<<< orphan*/  fpu_ymmh0; int /*<<< orphan*/  fpu_zmmh0; int /*<<< orphan*/  fpu_k0; } ;
typedef  TYPE_8__ x86_avx512_state32_t ;
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ thread_state_t ;
typedef  scalar_t__ thread_flavor_t ;
struct x86_fx_thread_state {scalar_t__ fp_valid; int /*<<< orphan*/  fp_save_layout; } ;
struct TYPE_12__ {int xstate_bv; int /*<<< orphan*/  xcomp_bv; int /*<<< orphan*/ * xhrsvd; } ;
struct TYPE_11__ {void* fp_save_layout; } ;
struct x86_avx_thread_state {TYPE_2__ _xh; int /*<<< orphan*/  x_YMM_Hi128; TYPE_1__ fp; } ;
struct TYPE_14__ {int /*<<< orphan*/  xcomp_bv; int /*<<< orphan*/  xstate_bv; int /*<<< orphan*/ * xhrsvd; } ;
struct TYPE_13__ {void* fp_save_layout; } ;
struct x86_avx512_thread_state {int /*<<< orphan*/  x_YMM_Hi128; int /*<<< orphan*/  x_ZMM_Hi256; int /*<<< orphan*/  x_Hi16_ZMM; int /*<<< orphan*/  x_Opmask; TYPE_4__ _xh; TYPE_3__ fp; } ;
typedef  TYPE_9__* pcb_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  _STRUCT_ZMM_REG ;
typedef  int /*<<< orphan*/  _STRUCT_YMM_REG ;
typedef  int /*<<< orphan*/  _STRUCT_XMM_REG ;
typedef  int /*<<< orphan*/  _STRUCT_OPMASK_REG ;
struct TYPE_19__ {int xstate; int /*<<< orphan*/  lock; struct x86_fx_thread_state* ifps; } ;

/* Variables and functions */
#define  AVX 135 
#define  AVX512 134 
 int /*<<< orphan*/  AVX512_XMASK ; 
 int AVX_XMASK ; 
 int /*<<< orphan*/  DBG_AVX512_STATE (struct x86_avx512_thread_state*) ; 
 scalar_t__ FALSE ; 
#define  FP 133 
 int /*<<< orphan*/  FXSAVE32 ; 
 int /*<<< orphan*/  FXSAVE64 ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ THREAD_NULL ; 
 TYPE_9__* THREAD_TO_PCB (scalar_t__) ; 
 scalar_t__ TRUE ; 
#define  UNDEFINED 132 
 int XFEM_SSE ; 
 int XFEM_X87 ; 
 void* XSAVE32 ; 
 void* XSAVE64 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy_nochk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ current_thread () ; 
 struct x86_fx_thread_state* fp_state_alloc (int) ; 
 int /*<<< orphan*/  fp_state_free (struct x86_fx_thread_state*,int) ; 
 int /*<<< orphan*/ * fp_state_size ; 
 scalar_t__ fpu_capability ; 
 int /*<<< orphan*/  fpu_thread_promote_avx512 (scalar_t__) ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  mxcsr_capability_mask ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  set_ts () ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_is_64bit_addr (scalar_t__) ; 
 int thread_xstate (scalar_t__) ; 
#define  x86_AVX512_STATE32 131 
#define  x86_AVX512_STATE64 130 
#define  x86_AVX_STATE32 129 
#define  x86_AVX_STATE64 128 

kern_return_t
fpu_set_fxstate(
	thread_t	thr_act,
	thread_state_t	tstate,
	thread_flavor_t f)
{
	struct x86_fx_thread_state	*ifps;
	struct x86_fx_thread_state	*new_ifps;
	x86_float_state64_t		*state;
	pcb_t				pcb;
	boolean_t			old_valid, fresh_state = FALSE;

	if (fpu_capability == UNDEFINED)
		return KERN_FAILURE;

	if ((f == x86_AVX_STATE32 || f == x86_AVX_STATE64) &&
	    fpu_capability < AVX)
		return KERN_FAILURE;

#if !defined(RC_HIDE_XNU_J137)
	if ((f == x86_AVX512_STATE32 || f == x86_AVX512_STATE64) &&
	    thread_xstate(thr_act) == AVX)
		if (!fpu_thread_promote_avx512(thr_act))
			return KERN_FAILURE;
#endif

	state = (x86_float_state64_t *)tstate;

	assert(thr_act != THREAD_NULL);
	pcb = THREAD_TO_PCB(thr_act);

	if (state == NULL) {
		/*
		 * new FPU state is 'invalid'.
		 * Deallocate the fp state if it exists.
		 */
		simple_lock(&pcb->lock);

		ifps = pcb->ifps;
		pcb->ifps = 0;

		simple_unlock(&pcb->lock);

		if (ifps != 0) {
			fp_state_free(ifps, thread_xstate(thr_act));
		}
	} else {
		/*
		 * Valid incoming state. Allocate the fp state if there is none.
		 */
		new_ifps = 0;
		Retry:
		simple_lock(&pcb->lock);

		ifps = pcb->ifps;
		if (ifps == 0) {
			if (new_ifps == 0) {
				simple_unlock(&pcb->lock);
				new_ifps = fp_state_alloc(thread_xstate(thr_act));
				goto Retry;
			}
			ifps = new_ifps;
			new_ifps = 0;
			pcb->ifps = ifps;
			pcb->xstate = thread_xstate(thr_act);
			fresh_state = TRUE;
		}

		/*
		 * now copy over the new data.
		 */

		old_valid = ifps->fp_valid;

#if	DEBUG || DEVELOPMENT
		if ((fresh_state == FALSE) && (old_valid == FALSE) && (thr_act != current_thread())) {
			panic("fpu_set_fxstate inconsistency, thread: %p not stopped", thr_act);
		}
#endif
		/*
		 * Clear any reserved bits in the MXCSR to prevent a GPF
		 * when issuing an FXRSTOR.
		 */

		state->fpu_mxcsr &= mxcsr_capability_mask;

		bcopy((char *)&state->fpu_fcw, (char *)ifps, fp_state_size[FP]);

		switch (thread_xstate(thr_act)) {
		    case UNDEFINED:
			panic("fpu_set_fxstate() UNDEFINED xstate");
			break;
		    case FP:
			ifps->fp_save_layout = thread_is_64bit_addr(thr_act) ? FXSAVE64 : FXSAVE32;
			break;
		    case AVX: {
			struct x86_avx_thread_state *iavx = (void *) ifps;
			x86_avx_state64_t *xs = (x86_avx_state64_t *) state;

			iavx->fp.fp_save_layout = thread_is_64bit_addr(thr_act) ? XSAVE64 : XSAVE32;

			/* Sanitize XSAVE header */
			bzero(&iavx->_xh.xhrsvd[0], sizeof(iavx->_xh.xhrsvd));
			iavx->_xh.xstate_bv = AVX_XMASK;
			iavx->_xh.xcomp_bv  = 0;

			if (f == x86_AVX_STATE32) {
				bcopy_nochk(&xs->fpu_ymmh0, iavx->x_YMM_Hi128, 8 * sizeof(_STRUCT_XMM_REG));
			} else if (f == x86_AVX_STATE64) {
				bcopy_nochk(&xs->fpu_ymmh0, iavx->x_YMM_Hi128, 16 * sizeof(_STRUCT_XMM_REG));
			} else {
				iavx->_xh.xstate_bv = (XFEM_SSE | XFEM_X87);
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

			iavx->fp.fp_save_layout = thread_is_64bit_addr(thr_act) ? XSAVE64 : XSAVE32;

			/* Sanitize XSAVE header */
			bzero(&iavx->_xh.xhrsvd[0], sizeof(iavx->_xh.xhrsvd));
			iavx->_xh.xstate_bv = AVX512_XMASK;
			iavx->_xh.xcomp_bv  = 0;

			switch (f) {
			    case x86_AVX512_STATE32:
				bcopy_nochk(&xs.s32->fpu_k0,    iavx->x_Opmask,     8 * sizeof(_STRUCT_OPMASK_REG));
				bcopy_nochk(&xs.s32->fpu_zmmh0, iavx->x_ZMM_Hi256,  8 * sizeof(_STRUCT_YMM_REG));
				bcopy_nochk(&xs.s32->fpu_ymmh0, iavx->x_YMM_Hi128,  8 * sizeof(_STRUCT_XMM_REG));
				DBG_AVX512_STATE(iavx);
				break;
			    case x86_AVX_STATE32:
				bcopy_nochk(&xs.s32->fpu_ymmh0, iavx->x_YMM_Hi128,  8 * sizeof(_STRUCT_XMM_REG));
				break;
			    case x86_AVX512_STATE64:
				bcopy_nochk(&xs.s64->fpu_k0,    iavx->x_Opmask,     8 * sizeof(_STRUCT_OPMASK_REG));
				bcopy_nochk(&xs.s64->fpu_zmm16, iavx->x_Hi16_ZMM,  16 * sizeof(_STRUCT_ZMM_REG));
				bcopy_nochk(&xs.s64->fpu_zmmh0, iavx->x_ZMM_Hi256, 16 * sizeof(_STRUCT_YMM_REG));
				bcopy_nochk(&xs.s64->fpu_ymmh0, iavx->x_YMM_Hi128, 16 * sizeof(_STRUCT_XMM_REG));
				DBG_AVX512_STATE(iavx);
				break;
			    case x86_AVX_STATE64:
				bcopy_nochk(&xs.s64->fpu_ymmh0, iavx->x_YMM_Hi128, 16 * sizeof(_STRUCT_XMM_REG));
				break;
			}
			break;
		    }
#endif
		}

		ifps->fp_valid = old_valid;

		if (old_valid == FALSE) {
			boolean_t istate = ml_set_interrupts_enabled(FALSE);
			ifps->fp_valid = TRUE;
			/* If altering the current thread's state, disable FPU */
			if (thr_act == current_thread())
				set_ts();

			ml_set_interrupts_enabled(istate);
		}

		simple_unlock(&pcb->lock);

		if (new_ifps != 0)
			fp_state_free(new_ifps, thread_xstate(thr_act));
	}
	return KERN_SUCCESS;
}