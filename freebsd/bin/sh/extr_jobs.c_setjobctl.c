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

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int getpgrp () ; 
 int /*<<< orphan*/  iflag ; 
 int initialpgrp ; 
 int /*<<< orphan*/  isatty (int) ; 
 int jobctl ; 
 int /*<<< orphan*/  jobctl_notty () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int rootpid ; 
 scalar_t__ rootshell ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsignal (int /*<<< orphan*/ ) ; 
 int tcgetpgrp (int) ; 
 int /*<<< orphan*/  tcsetpgrp (int,int) ; 
 int ttyfd ; 

void
setjobctl(int on)
{
	int i;

	if (on == jobctl || rootshell == 0)
		return;
	if (on) {
		if (ttyfd != -1)
			close(ttyfd);
		if ((ttyfd = open(_PATH_TTY, O_RDWR | O_CLOEXEC)) < 0) {
			i = 0;
			while (i <= 2 && !isatty(i))
				i++;
			if (i > 2 ||
			    (ttyfd = fcntl(i, F_DUPFD_CLOEXEC, 10)) < 0) {
				jobctl_notty();
				return;
			}
		}
		if (ttyfd < 10) {
			/*
			 * Keep our TTY file descriptor out of the way of
			 * the user's redirections.
			 */
			if ((i = fcntl(ttyfd, F_DUPFD_CLOEXEC, 10)) < 0) {
				jobctl_notty();
				return;
			}
			close(ttyfd);
			ttyfd = i;
		}
		do { /* while we are in the background */
			initialpgrp = tcgetpgrp(ttyfd);
			if (initialpgrp < 0) {
				jobctl_notty();
				return;
			}
			if (initialpgrp != getpgrp()) {
				if (!iflag) {
					initialpgrp = -1;
					jobctl_notty();
					return;
				}
				kill(0, SIGTTIN);
				continue;
			}
		} while (0);
		setsignal(SIGTSTP);
		setsignal(SIGTTOU);
		setsignal(SIGTTIN);
		setpgid(0, rootpid);
		tcsetpgrp(ttyfd, rootpid);
	} else { /* turning job control off */
		setpgid(0, initialpgrp);
		if (ttyfd >= 0) {
			tcsetpgrp(ttyfd, initialpgrp);
			close(ttyfd);
			ttyfd = -1;
		}
		setsignal(SIGTSTP);
		setsignal(SIGTTOU);
		setsignal(SIGTTIN);
	}
	jobctl = on;
}