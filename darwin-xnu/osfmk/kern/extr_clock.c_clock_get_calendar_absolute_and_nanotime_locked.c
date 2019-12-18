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
typedef  int /*<<< orphan*/  uint64_t ;
struct bintime {int dummy; } ;
typedef  int /*<<< orphan*/  clock_usec_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;
struct TYPE_2__ {int /*<<< orphan*/  bintime; } ;

/* Variables and functions */
 int /*<<< orphan*/  bintime2nsclock (struct bintime*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bintime_add (struct bintime*,int /*<<< orphan*/ *) ; 
 TYPE_1__ clock_calend ; 
 struct bintime get_scaled_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 

__attribute__((used)) static void
clock_get_calendar_absolute_and_nanotime_locked(
	clock_sec_t		*secs,
	clock_usec_t		*nanosecs,
	uint64_t    		*abstime)
{
	uint64_t now;
	struct bintime bt;

	now  = mach_absolute_time();
	if (abstime)
		*abstime = now;

	bt = get_scaled_time(now);
	bintime_add(&bt, &clock_calend.bintime);
	bintime2nsclock(&bt, secs, nanosecs);
}