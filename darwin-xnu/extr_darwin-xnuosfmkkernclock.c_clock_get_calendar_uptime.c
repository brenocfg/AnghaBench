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
struct bintime {int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bintime_add (struct bintime*,int /*<<< orphan*/ *) ; 
 TYPE_1__ clock_calend ; 
 int /*<<< orphan*/  clock_lock () ; 
 int /*<<< orphan*/  clock_unlock () ; 
 struct bintime get_scaled_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

void
clock_get_calendar_uptime(clock_sec_t *secs)
{
	uint64_t now;
	spl_t s;
	struct bintime bt;

	s = splclock();
	clock_lock();

	now = mach_absolute_time();

	bt = get_scaled_time(now);
	bintime_add(&bt, &clock_calend.offset);

	*secs = bt.sec;

	clock_unlock();
	splx(s);
}