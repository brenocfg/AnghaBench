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
struct request_queue {int /*<<< orphan*/  unplug_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_PLUGGED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  queue_flag_test_and_clear (int /*<<< orphan*/ ,struct request_queue*) ; 

int blk_remove_plug(struct request_queue *q)
{
	WARN_ON(!irqs_disabled());

	if (!queue_flag_test_and_clear(QUEUE_FLAG_PLUGGED, q))
		return 0;

	del_timer(&q->unplug_timer);
	return 1;
}