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
struct snd_timer_instance {int /*<<< orphan*/  flags; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  (* start ) (struct snd_timer*) ;} ;
struct snd_timer {unsigned long sticks; scalar_t__ running; TYPE_1__ hw; int /*<<< orphan*/  flags; int /*<<< orphan*/  active_list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_FLG_RESCHED ; 
 int SNDRV_TIMER_HW_SLAVE ; 
 int /*<<< orphan*/  SNDRV_TIMER_IFLG_RUNNING ; 
 int /*<<< orphan*/  SNDRV_TIMER_IFLG_START ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_timer*) ; 

__attribute__((used)) static int snd_timer_start1(struct snd_timer *timer, struct snd_timer_instance *timeri,
			    unsigned long sticks)
{
	list_del(&timeri->active_list);
	list_add_tail(&timeri->active_list, &timer->active_list_head);
	if (timer->running) {
		if (timer->hw.flags & SNDRV_TIMER_HW_SLAVE)
			goto __start_now;
		timer->flags |= SNDRV_TIMER_FLG_RESCHED;
		timeri->flags |= SNDRV_TIMER_IFLG_START;
		return 1;	/* delayed start */
	} else {
		timer->sticks = sticks;
		timer->hw.start(timer);
	      __start_now:
		timer->running++;
		timeri->flags |= SNDRV_TIMER_IFLG_RUNNING;
		return 0;
	}
}