#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int xstate_t ;
struct x86_fx_thread_state {int /*<<< orphan*/  fp_save_layout; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNED (struct x86_fx_thread_state*,int) ; 
#define  AVX 130 
#define  AVX512 129 
#define  FP 128 
 int /*<<< orphan*/  FXSAVE32 ; 
 int /*<<< orphan*/  FXSAVE64 ; 
 int /*<<< orphan*/  XSAVE32 ; 
 int /*<<< orphan*/  XSAVE64 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int current_xstate () ; 
 int /*<<< orphan*/  fxsave (void*) ; 
 int /*<<< orphan*/  fxsave64 (void*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  xsave (struct x86_fx_thread_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsave64 (struct x86_fx_thread_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xstate_xmask ; 

__attribute__((used)) static void fpu_store_registers(void *fstate, boolean_t is64) {
	struct x86_fx_thread_state *ifps = fstate;
	assert(ALIGNED(ifps, 64));
	xstate_t xs = current_xstate();
	switch (xs) {
	    case FP:
		if (is64) {
			fxsave64(fstate);
			ifps->fp_save_layout = FXSAVE64;
		} else {
			fxsave(fstate);
			ifps->fp_save_layout = FXSAVE32;
		}
		break;
	    case AVX:
#if !defined(RC_HIDE_XNU_J137)
	    case AVX512:
#endif
		if (is64) {
			xsave64(ifps, xstate_xmask[xs]);
			ifps->fp_save_layout = XSAVE64;
		} else {
			xsave(ifps, xstate_xmask[xs]);
			ifps->fp_save_layout = XSAVE32;
		}
		break;
	    default:
		panic("fpu_store_registers() bad xstate: %d\n", xs);
	}
}