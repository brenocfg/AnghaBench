#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct as_io_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  last_end_request; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct as_io_context* aic; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_TASK_IORUNNING ; 
 TYPE_1__* RQ_IOC (struct request*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  put_io_context (TYPE_1__*) ; 
 scalar_t__ rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void as_put_io_context(struct request *rq)
{
	struct as_io_context *aic;

	if (unlikely(!RQ_IOC(rq)))
		return;

	aic = RQ_IOC(rq)->aic;

	if (rq_is_sync(rq) && aic) {
		unsigned long flags;

		spin_lock_irqsave(&aic->lock, flags);
		set_bit(AS_TASK_IORUNNING, &aic->state);
		aic->last_end_request = jiffies;
		spin_unlock_irqrestore(&aic->lock, flags);
	}

	put_io_context(RQ_IOC(rq));
}