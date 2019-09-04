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
typedef  int /*<<< orphan*/  mach_timespec_t ;
typedef  int alarm_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_MACH_TIMESPEC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ALRMTYPE ; 
 scalar_t__ BAD_ALRMTYPE (int) ; 
 scalar_t__ BAD_MACH_TIMESPEC (int /*<<< orphan*/ *) ; 
 int CMP_MACH_TIMESPEC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TIME_RELATIVE ; 

__attribute__((used)) static int
check_time(
	alarm_type_t		alarm_type,
	mach_timespec_t		*alarm_time,
	mach_timespec_t		*clock_time)
{
	int					result;

	if (BAD_ALRMTYPE(alarm_type))
		return (-1);
	if (BAD_MACH_TIMESPEC(alarm_time))
		return (-1);
	if ((alarm_type & ALRMTYPE) == TIME_RELATIVE)
		ADD_MACH_TIMESPEC(alarm_time, clock_time);

	result = CMP_MACH_TIMESPEC(alarm_time, clock_time);

	return ((result >= 0)? result: 0);
}