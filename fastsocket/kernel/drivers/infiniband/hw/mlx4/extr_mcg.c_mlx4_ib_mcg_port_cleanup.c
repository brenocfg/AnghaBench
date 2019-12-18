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
struct mlx4_ib_demux_ctx {int flushing; } ;
struct clean_work {int destroy_wq; int /*<<< orphan*/  work; struct mlx4_ib_demux_ctx* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mlx4_ib_mcg_port_cleanup (struct mlx4_ib_demux_ctx*,int) ; 
 int /*<<< orphan*/  clean_wq ; 
 struct clean_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcg_clean_task ; 
 int /*<<< orphan*/  mcg_warn (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx4_ib_mcg_port_cleanup(struct mlx4_ib_demux_ctx *ctx, int destroy_wq)
{
	struct clean_work *work;

	if (ctx->flushing)
		return;

	ctx->flushing = 1;

	if (destroy_wq) {
		_mlx4_ib_mcg_port_cleanup(ctx, destroy_wq);
		ctx->flushing = 0;
		return;
	}

	work = kmalloc(sizeof *work, GFP_KERNEL);
	if (!work) {
		ctx->flushing = 0;
		mcg_warn("failed allocating work for cleanup\n");
		return;
	}

	work->ctx = ctx;
	work->destroy_wq = destroy_wq;
	INIT_WORK(&work->work, mcg_clean_task);
	queue_work(clean_wq, &work->work);
}