#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uld_ctx {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  oc_mw_kva; } ;
struct TYPE_3__ {int /*<<< orphan*/  ibdev; TYPE_2__ rdev; int /*<<< orphan*/  mmidr; int /*<<< orphan*/  qpidr; int /*<<< orphan*/  cqidr; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_rdev_close (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c4iw_dealloc(struct uld_ctx *ctx)
{
	c4iw_rdev_close(&ctx->dev->rdev);
	idr_destroy(&ctx->dev->cqidr);
	idr_destroy(&ctx->dev->qpidr);
	idr_destroy(&ctx->dev->mmidr);
	iounmap(ctx->dev->rdev.oc_mw_kva);
	ib_dealloc_device(&ctx->dev->ibdev);
	ctx->dev = NULL;
}