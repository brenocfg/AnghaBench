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
struct snd_seq_timer {int ppq; int /*<<< orphan*/  lock; int /*<<< orphan*/  tempo; int /*<<< orphan*/  tick; scalar_t__ running; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  snd_seq_timer_set_tick_resolution (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_timer_set_ppq(struct snd_seq_timer * tmr, int ppq)
{
	unsigned long flags;

	if (snd_BUG_ON(!tmr))
		return -EINVAL;
	if (ppq <= 0)
		return -EINVAL;
	spin_lock_irqsave(&tmr->lock, flags);
	if (tmr->running && (ppq != tmr->ppq)) {
		/* refuse to change ppq on running timers */
		/* because it will upset the song position (ticks) */
		spin_unlock_irqrestore(&tmr->lock, flags);
		snd_printd("seq: cannot change ppq of a running timer\n");
		return -EBUSY;
	}

	tmr->ppq = ppq;
	snd_seq_timer_set_tick_resolution(&tmr->tick, tmr->tempo, tmr->ppq);
	spin_unlock_irqrestore(&tmr->lock, flags);
	return 0;
}