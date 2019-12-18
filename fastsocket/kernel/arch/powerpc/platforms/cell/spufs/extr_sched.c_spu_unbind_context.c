#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {scalar_t__ class2_intr_base; int /*<<< orphan*/  class2_intr; scalar_t__ slb_flt_base; int /*<<< orphan*/  slb_flt; } ;
struct spu_context {int /*<<< orphan*/  stop_wq; int /*<<< orphan*/ * spu; TYPE_4__ stats; int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; int /*<<< orphan*/  csa; TYPE_1__* gang; } ;
struct TYPE_8__ {scalar_t__ class2_intr; scalar_t__ slb_flt; } ;
struct spu {size_t node; TYPE_3__ stats; int /*<<< orphan*/  register_lock; TYPE_2__* ctx; scalar_t__ flags; scalar_t__ tgid; scalar_t__ pid; int /*<<< orphan*/ * mfc_callback; int /*<<< orphan*/ * stop_callback; int /*<<< orphan*/ * wbox_callback; int /*<<< orphan*/ * ibox_callback; int /*<<< orphan*/  timestamp; } ;
struct TYPE_10__ {int /*<<< orphan*/  reserved_spus; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  aff_sched_count; } ;

/* Variables and functions */
 int SPU_CREATE_NOSCHED ; 
 int /*<<< orphan*/  SPU_STATE_SAVED ; 
 int /*<<< orphan*/  SPU_UTIL_IDLE_LOADED ; 
 int /*<<< orphan*/  SPU_UTIL_SYSTEM ; 
 int /*<<< orphan*/  SWITCH_LOG_STOP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 TYPE_5__* cbe_spu_info ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_associate_mm (struct spu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_backing_ops ; 
 int /*<<< orphan*/  spu_context_trace (int /*<<< orphan*/ ,struct spu_context*,struct spu*) ; 
 int /*<<< orphan*/  spu_save (int /*<<< orphan*/ *,struct spu*) ; 
 scalar_t__ spu_stopped (struct spu_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_switch_log_notify (struct spu*,struct spu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_switch_notify (struct spu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_unbind_context__enter ; 
 int /*<<< orphan*/  spu_unmap_mappings (struct spu_context*) ; 
 int /*<<< orphan*/  spuctx_switch_state (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_unbind_context(struct spu *spu, struct spu_context *ctx)
{
	u32 status;

	spu_context_trace(spu_unbind_context__enter, ctx, spu);

	spuctx_switch_state(ctx, SPU_UTIL_SYSTEM);

 	if (spu->ctx->flags & SPU_CREATE_NOSCHED)
		atomic_dec(&cbe_spu_info[spu->node].reserved_spus);

	if (ctx->gang)
		/*
		 * If ctx->gang->aff_sched_count is positive, SPU affinity is
		 * being considered in this gang. Using atomic_dec_if_positive
		 * allow us to skip an explicit check for affinity in this gang
		 */
		atomic_dec_if_positive(&ctx->gang->aff_sched_count);

	spu_switch_notify(spu, NULL);
	spu_unmap_mappings(ctx);
	spu_save(&ctx->csa, spu);
	spu_switch_log_notify(spu, ctx, SWITCH_LOG_STOP, 0);

	spin_lock_irq(&spu->register_lock);
	spu->timestamp = jiffies;
	ctx->state = SPU_STATE_SAVED;
	spu->ibox_callback = NULL;
	spu->wbox_callback = NULL;
	spu->stop_callback = NULL;
	spu->mfc_callback = NULL;
	spu->pid = 0;
	spu->tgid = 0;
	ctx->ops = &spu_backing_ops;
	spu->flags = 0;
	spu->ctx = NULL;
	spin_unlock_irq(&spu->register_lock);

	spu_associate_mm(spu, NULL);

	ctx->stats.slb_flt +=
		(spu->stats.slb_flt - ctx->stats.slb_flt_base);
	ctx->stats.class2_intr +=
		(spu->stats.class2_intr - ctx->stats.class2_intr_base);

	/* This maps the underlying spu state to idle */
	spuctx_switch_state(ctx, SPU_UTIL_IDLE_LOADED);
	ctx->spu = NULL;

	if (spu_stopped(ctx, &status))
		wake_up_all(&ctx->stop_wq);
}