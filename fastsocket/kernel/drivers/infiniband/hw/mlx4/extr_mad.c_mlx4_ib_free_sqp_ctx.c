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
struct mlx4_ib_demux_pv_ctx {scalar_t__ state; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * pd; int /*<<< orphan*/ * mr; TYPE_1__* qp; scalar_t__ has_smi; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {int /*<<< orphan*/ * qp; } ;

/* Variables and functions */
 scalar_t__ DEMUX_PV_STATE_DOWN ; 
 scalar_t__ DEMUX_PV_STATE_DOWNING ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  IB_QPT_SMI ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dereg_mr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_free_pv_qp_bufs (struct mlx4_ib_demux_pv_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_ib_free_sqp_ctx(struct mlx4_ib_demux_pv_ctx *sqp_ctx)
{
	if (sqp_ctx->state > DEMUX_PV_STATE_DOWN) {
		sqp_ctx->state = DEMUX_PV_STATE_DOWNING;
		flush_workqueue(sqp_ctx->wq);
		if (sqp_ctx->has_smi) {
			ib_destroy_qp(sqp_ctx->qp[0].qp);
			sqp_ctx->qp[0].qp = NULL;
			mlx4_ib_free_pv_qp_bufs(sqp_ctx, IB_QPT_SMI, 0);
		}
		ib_destroy_qp(sqp_ctx->qp[1].qp);
		sqp_ctx->qp[1].qp = NULL;
		mlx4_ib_free_pv_qp_bufs(sqp_ctx, IB_QPT_GSI, 0);
		ib_dereg_mr(sqp_ctx->mr);
		sqp_ctx->mr = NULL;
		ib_dealloc_pd(sqp_ctx->pd);
		sqp_ctx->pd = NULL;
		ib_destroy_cq(sqp_ctx->cq);
		sqp_ctx->cq = NULL;
		sqp_ctx->state = DEMUX_PV_STATE_DOWN;
	}
}