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
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timeb {int millitm; scalar_t__ dstflag; scalar_t__ timezone; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

int ftime(struct timeb *tp)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	tp->time = ts.tv_sec;
	tp->millitm = ts.tv_nsec / 1000000;
	tp->timezone = tp->dstflag = 0;
	return 0;
}