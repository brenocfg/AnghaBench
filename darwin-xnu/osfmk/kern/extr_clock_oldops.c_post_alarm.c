#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_timespec_t ;
typedef  TYPE_1__* alarm_t ;
struct TYPE_4__ {struct TYPE_4__* al_prev; struct TYPE_4__* al_next; int /*<<< orphan*/  al_time; } ;

/* Variables and functions */
 scalar_t__ CMP_MACH_TIMESPEC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* alrmlist ; 
 int /*<<< orphan*/  set_alarm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
post_alarm(
	alarm_t				alarm)
{
	alarm_t	alrm1, alrm2;
	mach_timespec_t		*alarm_time;
	mach_timespec_t		*queue_time;

	/*
	 * Traverse alarm list until queue time is greater
	 * than alarm time, then insert alarm.
	 */
	alarm_time = &alarm->al_time;
	alrm1 = (alarm_t)&alrmlist;
	while ((alrm2 = alrm1->al_next) != NULL) {
		queue_time = &alrm2->al_time;
		if (CMP_MACH_TIMESPEC(queue_time, alarm_time) > 0)
			break;
		alrm1 = alrm2;
	}
	alrm1->al_next = alarm;
	alarm->al_next = alrm2;
	alarm->al_prev = alrm1;
	if (alrm2)
		alrm2->al_prev  = alarm;

	/*
	 * If the inserted alarm is the 'earliest' alarm,
	 * reset the device layer alarm time accordingly.
	 */
	if (alrmlist == alarm)
		set_alarm(alarm_time);
}