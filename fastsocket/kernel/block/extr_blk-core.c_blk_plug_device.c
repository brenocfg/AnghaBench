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
struct request_queue {scalar_t__ unplug_delay; int /*<<< orphan*/  unplug_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_PLUGGED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ blk_queue_stopped (struct request_queue*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  queue_flag_test_and_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  trace_block_plug (struct request_queue*) ; 

void blk_plug_device(struct request_queue *q)
{
	WARN_ON(!irqs_disabled());

	/*
	 * don't plug a stopped queue, it must be paired with blk_start_queue()
	 * which will restart the queueing
	 */
	if (blk_queue_stopped(q))
		return;

	if (!queue_flag_test_and_set(QUEUE_FLAG_PLUGGED, q)) {
		mod_timer(&q->unplug_timer, jiffies + q->unplug_delay);
		trace_block_plug(q);
	}
}