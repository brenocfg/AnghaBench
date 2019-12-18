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
struct uld_ctx {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ db_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  qpidr; } ;

/* Variables and functions */
 scalar_t__ FLOW_CONTROL ; 
 scalar_t__ NORMAL ; 
 int /*<<< orphan*/  disable_qp_db ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_queues(struct uld_ctx *ctx)
{
	spin_lock_irq(&ctx->dev->lock);
	if (ctx->dev->db_state == NORMAL) {
		ctx->dev->db_state = FLOW_CONTROL;
		idr_for_each(&ctx->dev->qpidr, disable_qp_db, NULL);
	}
	spin_unlock_irq(&ctx->dev->lock);
}