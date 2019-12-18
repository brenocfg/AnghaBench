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
struct timezone {scalar_t__ tz_dsttime; scalar_t__ tz_minuteswest; } ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct _reent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettick () ; 
 int ticks_to_microsecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int __libogc_gettod_r(struct _reent *ptr, struct timeval *tp, struct timezone *tz) {

	if (tp != NULL) {
		tp->tv_sec = time(NULL);
		tp->tv_usec = ticks_to_microsecs(gettick())%1000000;
	}
	if (tz != NULL) {
		tz->tz_minuteswest = 0;
		tz->tz_dsttime = 0;

	}
	return 0;
}