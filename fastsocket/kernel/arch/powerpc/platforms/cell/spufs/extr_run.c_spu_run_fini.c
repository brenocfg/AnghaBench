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
struct spu_context {int /*<<< orphan*/  sched_flags; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* npc_read ) (struct spu_context*) ;int /*<<< orphan*/  (* status_read ) (struct spu_context*) ;} ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  SPU_SCHED_SPU_RUN ; 
 int /*<<< orphan*/  SPU_UTIL_IDLE_LOADED ; 
 int /*<<< orphan*/  SWITCH_LOG_EXIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_del_from_rq (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int /*<<< orphan*/  spu_switch_log_notify (int /*<<< orphan*/ *,struct spu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spuctx_switch_state (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spu_context*) ; 
 int /*<<< orphan*/  stub2 (struct spu_context*) ; 

__attribute__((used)) static int spu_run_fini(struct spu_context *ctx, u32 *npc,
			       u32 *status)
{
	int ret = 0;

	spu_del_from_rq(ctx);

	*status = ctx->ops->status_read(ctx);
	*npc = ctx->ops->npc_read(ctx);

	spuctx_switch_state(ctx, SPU_UTIL_IDLE_LOADED);
	clear_bit(SPU_SCHED_SPU_RUN, &ctx->sched_flags);
	spu_switch_log_notify(NULL, ctx, SWITCH_LOG_EXIT, *status);
	spu_release(ctx);

	if (signal_pending(current))
		ret = -ERESTARTSYS;

	return ret;
}