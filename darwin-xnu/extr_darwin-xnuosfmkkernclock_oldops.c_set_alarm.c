#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_1__ mach_timespec_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TIMER_CALL_USER_NORMAL ; 
 int /*<<< orphan*/  alarm_expire_timer ; 
 int /*<<< orphan*/  nanotime_to_absolutetime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_enter_with_leeway (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_alarm(
	mach_timespec_t		*alarm_time)
{
	uint64_t	abstime;

	nanotime_to_absolutetime(alarm_time->tv_sec, alarm_time->tv_nsec, &abstime);
	timer_call_enter_with_leeway(&alarm_expire_timer, NULL, abstime, 0, TIMER_CALL_USER_NORMAL, FALSE);
}