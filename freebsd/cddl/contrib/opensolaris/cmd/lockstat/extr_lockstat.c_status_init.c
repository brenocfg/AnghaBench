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
typedef  int /*<<< orphan*/  timer_t ;
struct sigevent {int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_2__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct itimerspec {TYPE_1__ it_value; TYPE_1__ it_interval; } ;
typedef  scalar_t__ dtrace_optval_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ NANOSEC ; 
 int /*<<< orphan*/  SIGEV_SIGNAL ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  TIMER_RELTIME ; 
 int /*<<< orphan*/  dfail (char*) ; 
 int dtrace_getopt (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  g_dtp ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_fire ; 
 int timer_create (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 int timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
status_init(void)
{
	dtrace_optval_t val, status, agg;
	struct sigaction act;
	struct itimerspec ts;
	struct sigevent ev;
	timer_t tid;

	if (dtrace_getopt(g_dtp, "statusrate", &status) == -1)
		dfail("failed to get 'statusrate'");

	if (dtrace_getopt(g_dtp, "aggrate", &agg) == -1)
		dfail("failed to get 'statusrate'");

	/*
	 * We would want to awaken at a rate that is the GCD of the statusrate
	 * and the aggrate -- but that seems a bit absurd.  Instead, we'll
	 * simply awaken at a rate that is the more frequent of the two, which
	 * assures that we're never later than the interval implied by the
	 * more frequent rate.
	 */
	val = status < agg ? status : agg;

	(void) sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = status_fire;
	(void) sigaction(SIGUSR1, &act, NULL);

	ev.sigev_notify = SIGEV_SIGNAL;
	ev.sigev_signo = SIGUSR1;

	if (timer_create(CLOCK_REALTIME, &ev, &tid) == -1)
		dfail("cannot create CLOCK_REALTIME timer");

	ts.it_value.tv_sec = val / NANOSEC;
	ts.it_value.tv_nsec = val % NANOSEC;
	ts.it_interval = ts.it_value;

	if (timer_settime(tid, TIMER_RELTIME, &ts, NULL) == -1)
		dfail("cannot set time on CLOCK_REALTIME timer");
}