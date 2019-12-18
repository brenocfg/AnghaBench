#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_3__ {int tv_sec; int tv_nsec; } ;
struct TYPE_4__ {TYPE_1__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ clock_getres (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 TYPE_2__ st ; 

double
secs_elapsed(void)
{
	struct timespec end, ts_res;
	double secs, res;

	if (clock_gettime(CLOCK_MONOTONIC, &end))
		err(1, "clock_gettime");
	if (clock_getres(CLOCK_MONOTONIC, &ts_res))
		err(1, "clock_getres");
	secs = (end.tv_sec - st.start.tv_sec) + \
	       (end.tv_nsec - st.start.tv_nsec) * 1e-9;
	res = ts_res.tv_sec + ts_res.tv_nsec * 1e-9;
	if (secs < res)
		secs = res;

	return (secs);
}