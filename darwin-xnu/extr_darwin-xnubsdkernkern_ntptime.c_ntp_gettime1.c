#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {unsigned long tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct TYPE_2__ {unsigned long tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct ntptimeval {int maxerror; int /*<<< orphan*/  time_state; int /*<<< orphan*/  tai; int /*<<< orphan*/  esterror; TYPE_1__ time; } ;

/* Variables and functions */
 int MAXFREQ ; 
 int /*<<< orphan*/  NTP_ASSERT_LOCKED () ; 
 int /*<<< orphan*/  TIME_ERROR ; 
 unsigned long last_time_maxerror_update ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 scalar_t__ ntp_is_time_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_esterror ; 
 int time_maxerror ; 
 int /*<<< orphan*/  time_state ; 
 int /*<<< orphan*/  time_status ; 
 int /*<<< orphan*/  time_tai ; 

__attribute__((used)) static void
ntp_gettime1(struct ntptimeval *ntvp)
{
	struct timespec atv;

	NTP_ASSERT_LOCKED();

	nanotime(&atv);
	ntvp->time.tv_sec = atv.tv_sec;
	ntvp->time.tv_nsec = atv.tv_nsec;
	if ((unsigned long)atv.tv_sec > last_time_maxerror_update) {
		time_maxerror += (MAXFREQ / 1000)*(atv.tv_sec-last_time_maxerror_update);
		last_time_maxerror_update = atv.tv_sec;
	}
	ntvp->maxerror = time_maxerror;
	ntvp->esterror = time_esterror;
	ntvp->tai = time_tai;
	ntvp->time_state = time_state;

	if (ntp_is_time_error(time_status))
		ntvp->time_state = TIME_ERROR;
}