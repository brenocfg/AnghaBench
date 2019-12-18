#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vio_pfo_op {int /*<<< orphan*/  hcall_err; } ;
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct nx_crypto_ctx {TYPE_1__* stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {struct vio_dev* viodev; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_error_pid; int /*<<< orphan*/  last_error; int /*<<< orphan*/  errors; int /*<<< orphan*/  sync_ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cond_resched () ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ nx_driver ; 
 int vio_h_cop_sync (struct vio_dev*,struct vio_pfo_op*) ; 

int nx_hcall_sync(struct nx_crypto_ctx *nx_ctx,
		  struct vio_pfo_op    *op,
		  u32                   may_sleep)
{
	int rc, retries = 10;
	struct vio_dev *viodev = nx_driver.viodev;

	atomic_inc(&(nx_ctx->stats->sync_ops));

	do {
		rc = vio_h_cop_sync(viodev, op);
	} while ((rc == -EBUSY && !may_sleep && retries--) ||
	         (rc == -EBUSY && may_sleep && cond_resched()));

	if (rc) {
		dev_dbg(&viodev->dev, "vio_h_cop_sync failed: rc: %d "
			"hcall rc: %ld\n", rc, op->hcall_err);
		atomic_inc(&(nx_ctx->stats->errors));
		atomic_set(&(nx_ctx->stats->last_error), op->hcall_err);
		atomic_set(&(nx_ctx->stats->last_error_pid), current->pid);
	}

	return rc;
}