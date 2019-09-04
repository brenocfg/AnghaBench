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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  clock_usec_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;

/* Variables and functions */
 int /*<<< orphan*/  clock_get_boottime_microtime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
boottime_timeval(struct timeval *tv)
{
	clock_sec_t		secs;
	clock_usec_t	microsecs;

	clock_get_boottime_microtime(&secs, &microsecs);

	tv->tv_sec = secs;
	tv->tv_usec = microsecs;
}