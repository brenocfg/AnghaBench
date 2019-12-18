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
typedef  union evrec {int dummy; } evrec ;
struct seq_oss_readq {int qlen; int maxlen; size_t tail; int /*<<< orphan*/  lock; int /*<<< orphan*/  midi_sleep; int /*<<< orphan*/ * q; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union evrec*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int
snd_seq_oss_readq_put_event(struct seq_oss_readq *q, union evrec *ev)
{
	unsigned long flags;

	spin_lock_irqsave(&q->lock, flags);
	if (q->qlen >= q->maxlen - 1) {
		spin_unlock_irqrestore(&q->lock, flags);
		return -ENOMEM;
	}

	memcpy(&q->q[q->tail], ev, sizeof(*ev));
	q->tail = (q->tail + 1) % q->maxlen;
	q->qlen++;

	/* wake up sleeper */
	if (waitqueue_active(&q->midi_sleep))
		wake_up(&q->midi_sleep);

	spin_unlock_irqrestore(&q->lock, flags);

	return 0;
}