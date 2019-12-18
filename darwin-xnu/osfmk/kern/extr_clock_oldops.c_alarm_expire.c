#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spl_t ;
typedef  void* mach_timespec_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  TYPE_2__* clock_t ;
typedef  TYPE_3__* alarm_t ;
struct TYPE_8__ {void* al_time; scalar_t__ al_status; struct TYPE_8__* al_prev; struct TYPE_8__* al_next; } ;
struct TYPE_7__ {TYPE_1__* cl_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* c_gettime ) (void**) ;} ;

/* Variables and functions */
 scalar_t__ ALARM_CLOCK ; 
 void* ALARM_DONE ; 
 scalar_t__ ALARM_SLEEP ; 
 scalar_t__ CMP_MACH_TIMESPEC (void**,void**) ; 
 int /*<<< orphan*/  LOCK_ALARM (int /*<<< orphan*/ ) ; 
 size_t SYSTEM_CLOCK ; 
 int /*<<< orphan*/  UNLOCK_ALARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarm_done_call ; 
 TYPE_3__* alrmdone ; 
 int /*<<< orphan*/  alrmlist ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* clock_list ; 
 int /*<<< orphan*/  set_alarm (void**) ; 
 int /*<<< orphan*/  stub1 (void**) ; 
 int /*<<< orphan*/  thread_call_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alarm_expire(void)
{
	clock_t				clock;
	alarm_t	alrm1;
	alarm_t	alrm2;
	mach_timespec_t		clock_time;
	mach_timespec_t		*alarm_time;
	spl_t				s;

	clock = &clock_list[SYSTEM_CLOCK];
	(*clock->cl_ops->c_gettime)(&clock_time);

	/*
	 * Update clock alarm list. Alarms that are due are moved
	 * to the alarmdone list to be serviced by a thread callout.
	 */
	LOCK_ALARM(s);
	alrm1 = (alarm_t)&alrmlist;
	while ((alrm2 = alrm1->al_next) != NULL) {
		alarm_time = &alrm2->al_time;
		if (CMP_MACH_TIMESPEC(alarm_time, &clock_time) > 0)
			break;

		/*
		 * Alarm has expired, so remove it from the
		 * clock alarm list.
		 */  
		if ((alrm1->al_next = alrm2->al_next) != NULL)
			(alrm1->al_next)->al_prev = alrm1;

		/*
		 * If a clock_sleep() alarm, wakeup the thread
		 * which issued the clock_sleep() call.
		 */
		if (alrm2->al_status == ALARM_SLEEP) {
			alrm2->al_next = NULL;
			alrm2->al_status = ALARM_DONE;
			alrm2->al_time = clock_time;
			thread_wakeup((event_t)alrm2);
		}

 		/*
		 * If a clock_alarm() alarm, place the alarm on
		 * the alarm done list and schedule the alarm
		 * delivery mechanism.
		 */
		else {
			assert(alrm2->al_status == ALARM_CLOCK);
			if ((alrm2->al_next = alrmdone) != NULL)
				alrmdone->al_prev = alrm2;
			else
				thread_call_enter(&alarm_done_call);
			alrm2->al_prev = (alarm_t)&alrmdone;
			alrmdone = alrm2;
			alrm2->al_status = ALARM_DONE;
			alrm2->al_time = clock_time;
		}
	}

	/*
	 * Setup to expire for the next pending alarm.
	 */
	if (alrm2)
		set_alarm(alarm_time);
	UNLOCK_ALARM(s);
}