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
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ clock_usec_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  scalar_t__ clock_nsec_t ;

/* Variables and functions */
 scalar_t__ clock_boottime ; 
 scalar_t__ clock_boottime_usec ; 
 int /*<<< orphan*/  clock_lock () ; 
 int /*<<< orphan*/  clock_unlock () ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

void
clock_get_boottime_microtime(
	clock_sec_t			*secs,
	clock_usec_t		*microsecs)
{
	spl_t	s;

	s = splclock();
	clock_lock();

	*secs = (clock_sec_t)clock_boottime;
	*microsecs = (clock_nsec_t)clock_boottime_usec;

	clock_unlock();
	splx(s);
}