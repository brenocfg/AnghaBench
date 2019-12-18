#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_timer_instance {int flags; int /*<<< orphan*/  active_list; int /*<<< orphan*/  ack_list; struct snd_timer* timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (struct snd_timer*) ;int /*<<< orphan*/  (* stop ) (struct snd_timer*) ;} ;
struct snd_timer {int flags; int /*<<< orphan*/  lock; TYPE_1__ hw; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int SNDRV_TIMER_EVENT_RESOLUTION ; 
 int SNDRV_TIMER_FLG_CHANGE ; 
 int SNDRV_TIMER_FLG_RESCHED ; 
 int SNDRV_TIMER_IFLG_RUNNING ; 
 int SNDRV_TIMER_IFLG_SLAVE ; 
 int SNDRV_TIMER_IFLG_START ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slave_active_lock ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_timer_notify1 (struct snd_timer_instance*,int) ; 
 int /*<<< orphan*/  snd_timer_reschedule (struct snd_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_timer*) ; 
 int /*<<< orphan*/  stub2 (struct snd_timer*) ; 

__attribute__((used)) static int _snd_timer_stop(struct snd_timer_instance * timeri,
			   int keep_flag, int event)
{
	struct snd_timer *timer;
	unsigned long flags;

	if (snd_BUG_ON(!timeri))
		return -ENXIO;

	if (timeri->flags & SNDRV_TIMER_IFLG_SLAVE) {
		if (!keep_flag) {
			spin_lock_irqsave(&slave_active_lock, flags);
			timeri->flags &= ~SNDRV_TIMER_IFLG_RUNNING;
			spin_unlock_irqrestore(&slave_active_lock, flags);
		}
		goto __end;
	}
	timer = timeri->timer;
	if (!timer)
		return -EINVAL;
	spin_lock_irqsave(&timer->lock, flags);
	list_del_init(&timeri->ack_list);
	list_del_init(&timeri->active_list);
	if ((timeri->flags & SNDRV_TIMER_IFLG_RUNNING) &&
	    !(--timer->running)) {
		timer->hw.stop(timer);
		if (timer->flags & SNDRV_TIMER_FLG_RESCHED) {
			timer->flags &= ~SNDRV_TIMER_FLG_RESCHED;
			snd_timer_reschedule(timer, 0);
			if (timer->flags & SNDRV_TIMER_FLG_CHANGE) {
				timer->flags &= ~SNDRV_TIMER_FLG_CHANGE;
				timer->hw.start(timer);
			}
		}
	}
	if (!keep_flag)
		timeri->flags &=
			~(SNDRV_TIMER_IFLG_RUNNING | SNDRV_TIMER_IFLG_START);
	spin_unlock_irqrestore(&timer->lock, flags);
      __end:
	if (event != SNDRV_TIMER_EVENT_RESOLUTION)
		snd_timer_notify1(timeri, event);
	return 0;
}