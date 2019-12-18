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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue_flags; int /*<<< orphan*/  limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_CLUSTER ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_stack_limits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void blk_queue_stack_limits(struct request_queue *t, struct request_queue *b)
{
	blk_stack_limits(&t->limits, &b->limits, 0);

	if (!t->queue_lock)
		WARN_ON_ONCE(1);
	else if (!test_bit(QUEUE_FLAG_CLUSTER, &b->queue_flags)) {
		unsigned long flags;
		spin_lock_irqsave(t->queue_lock, flags);
		queue_flag_clear(QUEUE_FLAG_CLUSTER, t);
		spin_unlock_irqrestore(t->queue_lock, flags);
	}
}