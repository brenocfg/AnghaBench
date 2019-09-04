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
typedef  scalar_t__ suseconds_t ;
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NTP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTP_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ USEC_PER_SEC ; 
 int /*<<< orphan*/  start_ntp_loop () ; 
 int time_adjtime ; 

__attribute__((used)) static int
kern_adjtime(struct timeval *delta)
{
	struct timeval atv;
	int64_t ltr, ltw;
	boolean_t enable;

	if (delta == NULL)
		return (EINVAL);

	ltw = (int64_t)delta->tv_sec * (int64_t)USEC_PER_SEC + delta->tv_usec;

	NTP_LOCK(enable);
	ltr = time_adjtime;
	time_adjtime = ltw;
#if DEVELOPEMNT || DEBUG
	if (g_should_log_clock_adjustments) {
		os_log(OS_LOG_DEFAULT, "%s:AFTER offset %lld freq %lld status %d constant %ld time_adjtime %lld\n",
		       __func__, time_offset, time_freq, time_status, time_constant, time_adjtime);
	}
#endif
	NTP_UNLOCK(enable);

	atv.tv_sec = ltr / (int64_t)USEC_PER_SEC;
	atv.tv_usec = ltr % (int64_t)USEC_PER_SEC;
	if (atv.tv_usec < 0) {
		atv.tv_usec += (suseconds_t)USEC_PER_SEC;
		atv.tv_sec--;
	}

	*delta = atv;

	start_ntp_loop();

	return (0);
}