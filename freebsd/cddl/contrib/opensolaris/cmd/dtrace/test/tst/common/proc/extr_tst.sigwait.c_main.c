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
typedef  int /*<<< orphan*/  timer_t ;
struct sigevent {int sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct TYPE_4__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct itimerspec {TYPE_2__ it_interval; TYPE_1__ it_value; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int NANOSEC ; 
 int /*<<< orphan*/  SIGEV_SIGNAL ; 
 int SIGUSR1 ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  TIMER_RELTIME ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigwait (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int timer_create (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 int timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
	struct sigevent ev;
	struct itimerspec ts;
	sigset_t set;
	timer_t tid;
	char *cmd = argv[0];
	int sig;

	ev.sigev_notify = SIGEV_SIGNAL;
	ev.sigev_signo = SIGUSR1;

	if (timer_create(CLOCK_REALTIME, &ev, &tid) == -1) {
		(void) fprintf(stderr, "%s: cannot create CLOCK_HIGHRES "
		    "timer: %s\n", cmd, strerror(errno));
		exit(EXIT_FAILURE);
	}

	(void) sigemptyset(&set);
	(void) sigaddset(&set, SIGUSR1);
	(void) sigprocmask(SIG_BLOCK, &set, NULL);

	ts.it_value.tv_sec = 1;
	ts.it_value.tv_nsec = 0;
	ts.it_interval.tv_sec = 0;
	ts.it_interval.tv_nsec = NANOSEC / 2;

	if (timer_settime(tid, TIMER_RELTIME, &ts, NULL) == -1) {
		(void) fprintf(stderr, "%s: timer_settime() failed: %s\n",
		    cmd, strerror(errno));
		exit(EXIT_FAILURE);
	}

	do {
		(void) sigwait(&set, &sig);
	} while(sig != SIGUSR1);

	/*NOTREACHED*/
	return (0);
}