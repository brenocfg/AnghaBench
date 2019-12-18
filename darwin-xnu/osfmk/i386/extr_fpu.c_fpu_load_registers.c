#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct x86_fx_thread_state {int fp_save_layout; } ;
struct TYPE_2__ {int xstate_bv; scalar_t__* xhrsvd; } ;
struct x86_avx_thread_state {TYPE_1__ _xh; } ;
typedef  int fp_save_layout_t ;

/* Variables and functions */
 int ALIGNED (struct x86_fx_thread_state*,int) ; 
 scalar_t__ FALSE ; 
#define  FXSAVE32 131 
#define  FXSAVE64 130 
#define  XSAVE32 129 
#define  XSAVE64 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 size_t current_xstate () ; 
 scalar_t__ fpu_YMM_capable ; 
 int /*<<< orphan*/  fxrstor (struct x86_fx_thread_state*) ; 
 int /*<<< orphan*/  fxrstor64 (struct x86_fx_thread_state*) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ thread_is_64bit_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xrstor (struct x86_fx_thread_state*,int) ; 
 int /*<<< orphan*/  xrstor64 (struct x86_fx_thread_state*,int) ; 
 int* xstate_xmask ; 

__attribute__((used)) static void fpu_load_registers(void *fstate) {
	struct x86_fx_thread_state *ifps = fstate;
	fp_save_layout_t layout = ifps->fp_save_layout;

	assert(current_task() == NULL ||				\
	       (thread_is_64bit_addr(current_thread()) ?			\
			(layout == FXSAVE64 || layout == XSAVE64) :	\
			(layout == FXSAVE32 || layout == XSAVE32)));
	assert(ALIGNED(ifps, 64));
	assert(ml_get_interrupts_enabled() == FALSE);

#if	DEBUG	
	if (layout == XSAVE32 || layout == XSAVE64) {
		struct x86_avx_thread_state *iavx = fstate;
		unsigned i;
		/* Verify reserved bits in the XSAVE header*/
		if (iavx->_xh.xstate_bv & ~xstate_xmask[current_xstate()])
			panic("iavx->_xh.xstate_bv: 0x%llx", iavx->_xh.xstate_bv);
		for (i = 0; i < sizeof(iavx->_xh.xhrsvd); i++)
			if (iavx->_xh.xhrsvd[i])
				panic("Reserved bit set");
	}
	if (fpu_YMM_capable) {
		if (layout != XSAVE32 && layout != XSAVE64)
			panic("Inappropriate layout: %u\n", layout);
	}
#endif	/* DEBUG */

	switch (layout) {
	    case FXSAVE64:
		fxrstor64(ifps);
		break;
	    case FXSAVE32:
		fxrstor(ifps);
		break;
	    case XSAVE64:
		xrstor64(ifps, xstate_xmask[current_xstate()]);
		break;
	    case XSAVE32:
		xrstor(ifps, xstate_xmask[current_xstate()]);
		break;
	    default:
		panic("fpu_load_registers() bad layout: %d\n", layout);
	}
}