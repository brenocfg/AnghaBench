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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;

/* Variables and functions */
 int /*<<< orphan*/  _absolutetime_to_nanotime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_nanotime_read () ; 

void
clock_get_system_nanotime(
	clock_sec_t			*secs,
	clock_nsec_t		*nanosecs)
{
	uint64_t	now = rtc_nanotime_read();

	_absolutetime_to_nanotime(now, secs, nanosecs);
}