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
typedef  int /*<<< orphan*/  u32 ;
struct spu_context {int flags; scalar_t__ state; int /*<<< orphan*/  sched_flags; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* status_read ) (struct spu_context*) ;unsigned long (* runcntl_read ) (struct spu_context*) ;int /*<<< orphan*/  (* runcntl_write ) (struct spu_context*,unsigned long) ;int /*<<< orphan*/  (* npc_write ) (struct spu_context*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* privcntl_write ) (struct spu_context*,unsigned long) ;} ;

/* Variables and functions */
 int SPU_CREATE_ISOLATE ; 
 int SPU_CREATE_NOSCHED ; 
 unsigned long SPU_PRIVCNTL_MODE_NORMAL ; 
 unsigned long SPU_PRIVCNTL_MODE_SINGLE_STEP ; 
 unsigned long SPU_RUNCNTL_ISOLATE ; 
 unsigned long SPU_RUNCNTL_RUNNABLE ; 
 int /*<<< orphan*/  SPU_SCHED_SPU_RUN ; 
 scalar_t__ SPU_STATE_SAVED ; 
 int SPU_STATUS_ISOLATED_STATE ; 
 int /*<<< orphan*/  SPU_UTIL_SYSTEM ; 
 int /*<<< orphan*/  SPU_UTIL_USER ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spu_activate (struct spu_context*,int /*<<< orphan*/ ) ; 
 int spu_setup_isolated (struct spu_context*) ; 
 int /*<<< orphan*/  spuctx_switch_state (struct spu_context*,int /*<<< orphan*/ ) ; 
 int stub1 (struct spu_context*) ; 
 unsigned long stub2 (struct spu_context*) ; 
 int /*<<< orphan*/  stub3 (struct spu_context*,unsigned long) ; 
 int /*<<< orphan*/  stub4 (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct spu_context*,unsigned long) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spu_run_init(struct spu_context *ctx, u32 *npc)
{
	unsigned long runcntl = SPU_RUNCNTL_RUNNABLE;
	int ret;

	spuctx_switch_state(ctx, SPU_UTIL_SYSTEM);

	/*
	 * NOSCHED is synchronous scheduling with respect to the caller.
	 * The caller waits for the context to be loaded.
	 */
	if (ctx->flags & SPU_CREATE_NOSCHED) {
		if (ctx->state == SPU_STATE_SAVED) {
			ret = spu_activate(ctx, 0);
			if (ret)
				return ret;
		}
	}

	/*
	 * Apply special setup as required.
	 */
	if (ctx->flags & SPU_CREATE_ISOLATE) {
		if (!(ctx->ops->status_read(ctx) & SPU_STATUS_ISOLATED_STATE)) {
			ret = spu_setup_isolated(ctx);
			if (ret)
				return ret;
		}

		/*
		 * If userspace has set the runcntrl register (eg, to
		 * issue an isolated exit), we need to re-set it here
		 */
		runcntl = ctx->ops->runcntl_read(ctx) &
			(SPU_RUNCNTL_RUNNABLE | SPU_RUNCNTL_ISOLATE);
		if (runcntl == 0)
			runcntl = SPU_RUNCNTL_RUNNABLE;
	} else {
		unsigned long privcntl;

		if (test_thread_flag(TIF_SINGLESTEP))
			privcntl = SPU_PRIVCNTL_MODE_SINGLE_STEP;
		else
			privcntl = SPU_PRIVCNTL_MODE_NORMAL;

		ctx->ops->privcntl_write(ctx, privcntl);
		ctx->ops->npc_write(ctx, *npc);
	}

	ctx->ops->runcntl_write(ctx, runcntl);

	if (ctx->flags & SPU_CREATE_NOSCHED) {
		spuctx_switch_state(ctx, SPU_UTIL_USER);
	} else {

		if (ctx->state == SPU_STATE_SAVED) {
			ret = spu_activate(ctx, 0);
			if (ret)
				return ret;
		} else {
			spuctx_switch_state(ctx, SPU_UTIL_USER);
		}
	}

	set_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags);
	return 0;
}