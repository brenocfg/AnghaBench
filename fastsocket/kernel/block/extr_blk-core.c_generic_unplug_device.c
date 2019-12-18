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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __generic_unplug_device (struct request_queue*) ; 
 scalar_t__ blk_queue_plugged (struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void generic_unplug_device(struct request_queue *q)
{
	if (blk_queue_plugged(q)) {
		spin_lock_irq(q->queue_lock);
		__generic_unplug_device(q);
		spin_unlock_irq(q->queue_lock);
	}
}