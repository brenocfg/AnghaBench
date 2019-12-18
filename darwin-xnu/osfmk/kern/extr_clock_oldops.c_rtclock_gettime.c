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
struct TYPE_3__ {unsigned int tv_sec; int /*<<< orphan*/  tv_nsec; } ;
typedef  TYPE_1__ mach_timespec_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  clock_get_system_nanotime (scalar_t__*,int /*<<< orphan*/ *) ; 

kern_return_t
rtclock_gettime(
	mach_timespec_t		*time)	/* OUT */
{
	clock_sec_t		secs;
	clock_nsec_t	nsecs;

	clock_get_system_nanotime(&secs, &nsecs);
	time->tv_sec = (unsigned int)secs;
	time->tv_nsec = nsecs;

	return (KERN_SUCCESS);
}