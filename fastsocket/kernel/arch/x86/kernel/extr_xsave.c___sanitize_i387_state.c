#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_8__ {TYPE_3__* xstate; } ;
struct task_struct {TYPE_4__ thread; } ;
struct i387_fxsave_struct {int cwd; int /*<<< orphan*/ * xmm_space; int /*<<< orphan*/ * st_space; scalar_t__ rdp; scalar_t__ rip; scalar_t__ fop; scalar_t__ twd; scalar_t__ swd; } ;
struct TYPE_5__ {int xstate_bv; } ;
struct TYPE_6__ {TYPE_1__ xsave_hdr; } ;
struct TYPE_7__ {TYPE_2__ xsave; struct i387_fxsave_struct fxsave; } ;

/* Variables and functions */
 int XSTATE_FP ; 
 int XSTATE_SSE ; 
 scalar_t__ init_xstate_buf ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pcntxt_mask ; 
 int* xstate_offsets ; 
 int* xstate_sizes ; 

void __sanitize_i387_state(struct task_struct *tsk)
{
	u64 xstate_bv;
	int feature_bit = 0x2;
	struct i387_fxsave_struct *fx = &tsk->thread.xstate->fxsave;

	if (!fx)
		return;

	xstate_bv = tsk->thread.xstate->xsave.xsave_hdr.xstate_bv;

	/*
	 * None of the feature bits are in init state. So nothing else
	 * to do for us, as the memory layout is upto date.
	 */
	if ((xstate_bv & pcntxt_mask) == pcntxt_mask)
		return;

	/*
	 * FP is in init state
	 */
	if (!(xstate_bv & XSTATE_FP)) {
		fx->cwd = 0x37f;
		fx->swd = 0;
		fx->twd = 0;
		fx->fop = 0;
		fx->rip = 0;
		fx->rdp = 0;
		memset(&fx->st_space[0], 0, 128);
	}

	/*
	 * SSE is in init state
	 */
	if (!(xstate_bv & XSTATE_SSE))
		memset(&fx->xmm_space[0], 0, 256);

	xstate_bv = (pcntxt_mask & ~xstate_bv) >> 2;

	/*
	 * Update all the other memory layouts for which the corresponding
	 * header bit is in the init state.
	 */
	while (xstate_bv) {
		if (xstate_bv & 0x1) {
			int offset = xstate_offsets[feature_bit];
			int size = xstate_sizes[feature_bit];

			memcpy(((void *) fx) + offset,
			       ((void *) init_xstate_buf) + offset,
			       size);
		}

		xstate_bv >>= 1;
		feature_bit++;
	}
}