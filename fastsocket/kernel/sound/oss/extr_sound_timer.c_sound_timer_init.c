#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sound_lowlev_timer {scalar_t__ priority; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ info; } ;

/* Variables and functions */
 int initialized ; 
 int sound_alloc_timerdev () ; 
 TYPE_2__ sound_timer ; 
 TYPE_2__** sound_timer_devs ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct sound_lowlev_timer* tmr ; 

void  sound_timer_init(struct sound_lowlev_timer *t, char *name)
{
	int n;

	if (initialized)
	{
		if (t->priority <= tmr->priority)
			return;	/* There is already a similar or better timer */
		tmr = t;
		return;
	}
	initialized = 1;
	tmr = t;

	n = sound_alloc_timerdev();
	if (n == -1)
		n = 0;		/* Overwrite the system timer */
	strcpy(sound_timer.info.name, name);
	sound_timer_devs[n] = &sound_timer;
}