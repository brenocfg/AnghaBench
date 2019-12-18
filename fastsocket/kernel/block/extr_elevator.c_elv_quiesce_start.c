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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  elevator; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_ELVSWITCH ; 
 int /*<<< orphan*/  blk_drain_queue (struct request_queue*,int) ; 
 int /*<<< orphan*/  queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void elv_quiesce_start(struct request_queue *q)
{
	if (!q->elevator)
		return;

	spin_lock_irq(q->queue_lock);
	queue_flag_set(QUEUE_FLAG_ELVSWITCH, q);
	spin_unlock_irq(q->queue_lock);

	blk_drain_queue(q, false);
}