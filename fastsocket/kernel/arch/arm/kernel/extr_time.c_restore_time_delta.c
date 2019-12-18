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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_settimeofday (struct timespec*) ; 
 int /*<<< orphan*/  set_normalized_timespec (struct timespec*,scalar_t__,scalar_t__) ; 

void restore_time_delta(struct timespec *delta, struct timespec *rtc)
{
	struct timespec ts;

	set_normalized_timespec(&ts,
				delta->tv_sec + rtc->tv_sec,
				delta->tv_nsec + rtc->tv_nsec);

	do_settimeofday(&ts);
}