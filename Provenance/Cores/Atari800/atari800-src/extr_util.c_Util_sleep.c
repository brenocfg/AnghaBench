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
struct timeval {double tv_usec; scalar_t__ tv_sec; } ;
struct timespec {double tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DosSleep (double) ; 
 int /*<<< orphan*/  PLATFORM_Sleep (double) ; 
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 double Util_time () ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  snooze (double) ; 
 int /*<<< orphan*/  usleep (double) ; 

void Util_sleep(double s)
{
#ifdef SUPPORTS_PLATFORM_SLEEP
	PLATFORM_Sleep(s);
#else /* !SUPPORTS_PLATFORM_SLEEP */
	if (s > 0) {
#ifdef HAVE_WINDOWS_H
		Sleep((DWORD) (s * 1e3));
#elif defined(DJGPP)
		/* DJGPP has usleep and select, but they don't work that good */
		/* XXX: find out why */
		double curtime = Util_time();
		while ((curtime + s) > Util_time());
#elif defined(HAVE_NANOSLEEP)
		struct timespec ts;
		ts.tv_sec = 0;
		ts.tv_nsec = s * 1e9;
		nanosleep(&ts, NULL);
#elif defined(HAVE_USLEEP)
		usleep(s * 1e6);
#elif defined(__BEOS__)
		/* added by Walter Las for BeOS */
		snooze(s * 1e6);
#elif defined(__EMX__)
		/* added by Brian Smith for os/2 */
		DosSleep(s);
#elif defined(HAVE_SELECT)
		/* linux */
		struct timeval tp;
		tp.tv_sec = 0;
		tp.tv_usec = s * 1e6;
		select(1, NULL, NULL, NULL, &tp);
#else
		double curtime = Util_time();
		while ((curtime + s) > Util_time());
#endif
	}
#endif /* !SUPPORTS_PLATFORM_SLEEP */
}