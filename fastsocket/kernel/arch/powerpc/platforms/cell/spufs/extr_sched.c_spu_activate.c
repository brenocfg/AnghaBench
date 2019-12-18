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
struct spu_context {int flags; TYPE_1__* ops; int /*<<< orphan*/  prio; scalar_t__ spu; } ;
struct spu {int dummy; } ;
struct TYPE_2__ {unsigned long (* runcntl_read ) (struct spu_context*) ;} ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int SPU_CREATE_NOSCHED ; 
 unsigned long SPU_RUNCNTL_RUNNABLE ; 
 int /*<<< orphan*/  SPU_UTIL_USER ; 
 int /*<<< orphan*/  __spu_schedule (struct spu*,struct spu_context*) ; 
 int /*<<< orphan*/  current ; 
 struct spu* find_victim (struct spu_context*) ; 
 scalar_t__ rt_prio (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_add_to_rq (struct spu_context*) ; 
 struct spu* spu_get_idle (struct spu_context*) ; 
 int /*<<< orphan*/  spu_prio_wait (struct spu_context*) ; 
 int /*<<< orphan*/  spuctx_switch_state (struct spu_context*,int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct spu_context*) ; 

int spu_activate(struct spu_context *ctx, unsigned long flags)
{
	struct spu *spu;

	/*
	 * If there are multiple threads waiting for a single context
	 * only one actually binds the context while the others will
	 * only be able to acquire the state_mutex once the context
	 * already is in runnable state.
	 */
	if (ctx->spu)
		return 0;

spu_activate_top:
	if (signal_pending(current))
		return -ERESTARTSYS;

	spu = spu_get_idle(ctx);
	/*
	 * If this is a realtime thread we try to get it running by
	 * preempting a lower priority thread.
	 */
	if (!spu && rt_prio(ctx->prio))
		spu = find_victim(ctx);
	if (spu) {
		unsigned long runcntl;

		runcntl = ctx->ops->runcntl_read(ctx);
		__spu_schedule(spu, ctx);
		if (runcntl & SPU_RUNCNTL_RUNNABLE)
			spuctx_switch_state(ctx, SPU_UTIL_USER);

		return 0;
	}

	if (ctx->flags & SPU_CREATE_NOSCHED) {
		spu_prio_wait(ctx);
		goto spu_activate_top;
	}

	spu_add_to_rq(ctx);

	return 0;
}