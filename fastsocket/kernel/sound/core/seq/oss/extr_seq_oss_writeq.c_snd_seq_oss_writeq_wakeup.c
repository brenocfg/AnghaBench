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
struct seq_oss_writeq {int /*<<< orphan*/  sync_lock; int /*<<< orphan*/  sync_sleep; scalar_t__ sync_event_put; int /*<<< orphan*/  sync_time; } ;
typedef  int /*<<< orphan*/  abstime_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void
snd_seq_oss_writeq_wakeup(struct seq_oss_writeq *q, abstime_t time)
{
	unsigned long flags;

	spin_lock_irqsave(&q->sync_lock, flags);
	q->sync_time = time;
	q->sync_event_put = 0;
	if (waitqueue_active(&q->sync_sleep)) {
		wake_up(&q->sync_sleep);
	}
	spin_unlock_irqrestore(&q->sync_lock, flags);
}