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
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_PROCESS_CPUTIME_ID ; 
 int LONG_MAX ; 
 scalar_t__ __clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

clock_t clock()
{
	struct timespec ts;

	if (__clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts))
		return -1;

	if (ts.tv_sec > LONG_MAX/1000000
	 || ts.tv_nsec/1000 > LONG_MAX-1000000*ts.tv_sec)
		return -1;

	return ts.tv_sec*1000000 + ts.tv_nsec/1000;
}