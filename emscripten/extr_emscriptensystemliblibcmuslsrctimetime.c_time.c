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
typedef  int /*<<< orphan*/  time_t ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  __clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

time_t time(time_t *t)
{
	struct timespec ts;
	__clock_gettime(CLOCK_REALTIME, &ts);
	if (t) *t = ts.tv_sec;
	return ts.tv_sec;
}