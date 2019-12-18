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
struct mlx4_ib_demux_ctx {int port; scalar_t__ flushing; int /*<<< orphan*/  mcg_mgid0_list; int /*<<< orphan*/  mcg_table; int /*<<< orphan*/  mcg_table_lock; int /*<<< orphan*/  mcg_wq; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int mlx4_ib_mcg_port_init(struct mlx4_ib_demux_ctx *ctx)
{
	char name[20];

	atomic_set(&ctx->tid, 0);
	sprintf(name, "mlx4_ib_mcg%d", ctx->port);
	ctx->mcg_wq = create_singlethread_workqueue(name);
	if (!ctx->mcg_wq)
		return -ENOMEM;

	mutex_init(&ctx->mcg_table_lock);
	ctx->mcg_table = RB_ROOT;
	INIT_LIST_HEAD(&ctx->mcg_mgid0_list);
	ctx->flushing = 0;

	return 0;
}