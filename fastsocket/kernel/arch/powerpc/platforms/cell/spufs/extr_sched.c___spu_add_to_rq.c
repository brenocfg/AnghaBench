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
struct spu_context {size_t prio; int /*<<< orphan*/  rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_waiting; int /*<<< orphan*/  bitmap; int /*<<< orphan*/ * runq; } ;

/* Variables and functions */
 scalar_t__ SPUSCHED_TICK ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* spu_prio ; 
 int /*<<< orphan*/  spusched_timer ; 

__attribute__((used)) static void __spu_add_to_rq(struct spu_context *ctx)
{
	/*
	 * Unfortunately this code path can be called from multiple threads
	 * on behalf of a single context due to the way the problem state
	 * mmap support works.
	 *
	 * Fortunately we need to wake up all these threads at the same time
	 * and can simply skip the runqueue addition for every but the first
	 * thread getting into this codepath.
	 *
	 * It's still quite hacky, and long-term we should proxy all other
	 * threads through the owner thread so that spu_run is in control
	 * of all the scheduling activity for a given context.
	 */
	if (list_empty(&ctx->rq)) {
		list_add_tail(&ctx->rq, &spu_prio->runq[ctx->prio]);
		set_bit(ctx->prio, spu_prio->bitmap);
		if (!spu_prio->nr_waiting++)
			mod_timer(&spusched_timer, jiffies + SPUSCHED_TICK);
	}
}