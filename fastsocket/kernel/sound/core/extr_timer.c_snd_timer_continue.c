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
struct snd_timer_instance {int flags; int cticks; scalar_t__ pticks; struct snd_timer* timer; } ;
struct snd_timer {int /*<<< orphan*/  lock; int /*<<< orphan*/  sticks; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_CONTINUE ; 
 int SNDRV_TIMER_IFLG_SLAVE ; 
 int /*<<< orphan*/  snd_timer_notify1 (struct snd_timer_instance*,int /*<<< orphan*/ ) ; 
 int snd_timer_start1 (struct snd_timer*,struct snd_timer_instance*,int /*<<< orphan*/ ) ; 
 int snd_timer_start_slave (struct snd_timer_instance*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_timer_continue(struct snd_timer_instance *timeri)
{
	struct snd_timer *timer;
	int result = -EINVAL;
	unsigned long flags;

	if (timeri == NULL)
		return result;
	if (timeri->flags & SNDRV_TIMER_IFLG_SLAVE)
		return snd_timer_start_slave(timeri);
	timer = timeri->timer;
	if (! timer)
		return -EINVAL;
	spin_lock_irqsave(&timer->lock, flags);
	if (!timeri->cticks)
		timeri->cticks = 1;
	timeri->pticks = 0;
	result = snd_timer_start1(timer, timeri, timer->sticks);
	spin_unlock_irqrestore(&timer->lock, flags);
	snd_timer_notify1(timeri, SNDRV_TIMER_EVENT_CONTINUE);
	return result;
}