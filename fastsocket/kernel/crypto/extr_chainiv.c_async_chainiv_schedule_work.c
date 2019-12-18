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
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct async_chainiv_ctx {int err; int /*<<< orphan*/  postponed; int /*<<< orphan*/  state; TYPE_1__ queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CHAINIV_STATE_INUSE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcrypto_wq ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int async_chainiv_schedule_work(struct async_chainiv_ctx *ctx)
{
	int queued;
	int err = ctx->err;

	if (!ctx->queue.qlen) {
		smp_mb__before_clear_bit();
		clear_bit(CHAINIV_STATE_INUSE, &ctx->state);

		if (!ctx->queue.qlen ||
		    test_and_set_bit(CHAINIV_STATE_INUSE, &ctx->state))
			goto out;
	}

	queued = queue_work(kcrypto_wq, &ctx->postponed);
	BUG_ON(!queued);

out:
	return err;
}