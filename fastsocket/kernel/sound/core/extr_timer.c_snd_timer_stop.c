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
struct snd_timer_instance {scalar_t__ pticks; int /*<<< orphan*/  ticks; int /*<<< orphan*/  cticks; struct snd_timer* timer; } ;
struct snd_timer {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_STOP ; 
 int _snd_timer_stop (struct snd_timer_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_timer_stop(struct snd_timer_instance *timeri)
{
	struct snd_timer *timer;
	unsigned long flags;
	int err;

	err = _snd_timer_stop(timeri, 0, SNDRV_TIMER_EVENT_STOP);
	if (err < 0)
		return err;
	timer = timeri->timer;
	if (!timer)
		return -EINVAL;
	spin_lock_irqsave(&timer->lock, flags);
	timeri->cticks = timeri->ticks;
	timeri->pticks = 0;
	spin_unlock_irqrestore(&timer->lock, flags);
	return 0;
}