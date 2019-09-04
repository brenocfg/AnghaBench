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
typedef  scalar_t__ uint64_t ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int /*<<< orphan*/ ,int,scalar_t__*) ; 

uint64_t
tstoabstime(struct timespec *ts)
{
	uint64_t abstime_s, abstime_ns;
	clock_interval_to_absolutetime_interval(ts->tv_sec, NSEC_PER_SEC, &abstime_s);
	clock_interval_to_absolutetime_interval(ts->tv_nsec, 1, &abstime_ns);
	return abstime_s + abstime_ns;
}