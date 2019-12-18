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
struct request_queue {int /*<<< orphan*/  unplug_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  kblockd_schedule_work (struct request_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_unplug_timer (struct request_queue*) ; 

void blk_unplug_timeout(unsigned long data)
{
	struct request_queue *q = (struct request_queue *)data;

	trace_block_unplug_timer(q);
	kblockd_schedule_work(q, &q->unplug_work);
}