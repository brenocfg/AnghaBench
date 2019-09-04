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
struct bintime {int /*<<< orphan*/  frac; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  clock_usec_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;
struct TYPE_2__ {int /*<<< orphan*/  tick_scale_x; int /*<<< orphan*/  bintime; } ;

/* Variables and functions */
 int /*<<< orphan*/  bintime2usclock (struct bintime*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bintime_add (struct bintime*,int /*<<< orphan*/ *) ; 
 TYPE_1__ clock_calend ; 
 int /*<<< orphan*/  clock_gettimeofday_set_commpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_lock () ; 
 int /*<<< orphan*/  clock_unlock () ; 
 struct bintime get_scaled_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks_per_sec ; 

void
clock_gettimeofday_and_absolute_time(
	clock_sec_t	*secs,
	clock_usec_t	*microsecs,
	uint64_t	*mach_time)
{
	uint64_t		now;
	spl_t			s;
	struct bintime 	bt;

	s = splclock();
	clock_lock();

	now = mach_absolute_time();
	bt = get_scaled_time(now);
	bintime_add(&bt, &clock_calend.bintime);
	bintime2usclock(&bt, secs, microsecs);

	clock_gettimeofday_set_commpage(now, bt.sec, bt.frac, clock_calend.tick_scale_x, ticks_per_sec);

	clock_unlock();
	splx(s);

	if (mach_time) {
		*mach_time = now;
	}
}