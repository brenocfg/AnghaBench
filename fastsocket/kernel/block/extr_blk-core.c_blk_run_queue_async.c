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
struct request_queue {int /*<<< orphan*/  delay_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_stopped (struct request_queue*) ; 
 int /*<<< orphan*/  kblockd_workqueue ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blk_run_queue_async(struct request_queue *q)
{
	if (likely(!blk_queue_stopped(q))) {
		__cancel_delayed_work(&q->delay_work);
		queue_delayed_work(kblockd_workqueue, &q->delay_work, 0);
	}
}