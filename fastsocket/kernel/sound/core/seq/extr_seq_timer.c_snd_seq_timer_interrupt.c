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
struct snd_timer_instance {struct snd_seq_queue* callback_data; } ;
struct snd_seq_timer {unsigned long skew; unsigned long skew_base; int /*<<< orphan*/  lock; int /*<<< orphan*/  last_update; int /*<<< orphan*/  tick; int /*<<< orphan*/  cur_time; int /*<<< orphan*/  running; } ;
struct snd_seq_queue {struct snd_seq_timer* timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_check_queue (struct snd_seq_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_inc_time_nsec (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  snd_seq_timer_update_tick (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_seq_timer_interrupt(struct snd_timer_instance *timeri,
				    unsigned long resolution,
				    unsigned long ticks)
{
	unsigned long flags;
	struct snd_seq_queue *q = timeri->callback_data;
	struct snd_seq_timer *tmr;

	if (q == NULL)
		return;
	tmr = q->timer;
	if (tmr == NULL)
		return;
	if (!tmr->running)
		return;

	resolution *= ticks;
	if (tmr->skew != tmr->skew_base) {
		/* FIXME: assuming skew_base = 0x10000 */
		resolution = (resolution >> 16) * tmr->skew +
			(((resolution & 0xffff) * tmr->skew) >> 16);
	}

	spin_lock_irqsave(&tmr->lock, flags);

	/* update timer */
	snd_seq_inc_time_nsec(&tmr->cur_time, resolution);

	/* calculate current tick */
	snd_seq_timer_update_tick(&tmr->tick, resolution);

	/* register actual time of this timer update */
	do_gettimeofday(&tmr->last_update);

	spin_unlock_irqrestore(&tmr->lock, flags);

	/* check queues and dispatch events */
	snd_seq_check_queue(q, 1, 0);
}