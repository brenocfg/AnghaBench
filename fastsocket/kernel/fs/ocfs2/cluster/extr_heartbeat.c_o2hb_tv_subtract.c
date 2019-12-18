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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static void o2hb_tv_subtract(struct timeval *a,
			     struct timeval *b)
{
	/* just return 0 when a is after b */
	if (a->tv_sec < b->tv_sec ||
	    (a->tv_sec == b->tv_sec && a->tv_usec < b->tv_usec)) {
		a->tv_sec = 0;
		a->tv_usec = 0;
		return;
	}

	a->tv_sec -= b->tv_sec;
	a->tv_usec -= b->tv_usec;
	while ( a->tv_usec < 0 ) {
		a->tv_sec--;
		a->tv_usec += 1000000;
	}
}