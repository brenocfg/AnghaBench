#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {TYPE_2__ total_sleep_time; TYPE_1__ wall_to_monotonic; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_normalized_timespec (struct timespec*,scalar_t__,scalar_t__) ; 
 TYPE_3__ timekeeper ; 

void getboottime(struct timespec *ts)
{
	struct timespec boottime = {
		.tv_sec = timekeeper.wall_to_monotonic.tv_sec +
				timekeeper.total_sleep_time.tv_sec,
		.tv_nsec = timekeeper.wall_to_monotonic.tv_nsec +
				timekeeper.total_sleep_time.tv_nsec
	};

	set_normalized_timespec(ts, -boottime.tv_sec, -boottime.tv_nsec);
}