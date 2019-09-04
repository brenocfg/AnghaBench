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
struct winsize {int dummy; } ;
struct termios {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_CLOEXEC ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fork () ; 
 scalar_t__ login_tty (int) ; 
 scalar_t__ openpty (int*,int*,char*,struct termios const*,struct winsize const*) ; 
 scalar_t__ pipe2 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ read (int,int*,int) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,int*,int) ; 

int forkpty(int *pm, char *name, const struct termios *tio, const struct winsize *ws)
{
	int m, s, ec=0, p[2], cs;
	pid_t pid=-1;
	sigset_t set, oldset;

	if (openpty(&m, &s, name, tio, ws) < 0) return -1;

	sigfillset(&set);
	pthread_sigmask(SIG_BLOCK, &set, &oldset);
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);

	if (pipe2(p, O_CLOEXEC)) {
		close(s);
		goto out;
	}

	pid = fork();
	if (!pid) {
		close(m);
		close(p[0]);
		if (login_tty(s)) {
			write(p[1], &errno, sizeof errno);
			_exit(127);
		}
		close(p[1]);
		pthread_setcancelstate(cs, 0);
		pthread_sigmask(SIG_SETMASK, &oldset, 0);
		return 0;
	}
	close(s);
	close(p[1]);
	if (read(p[0], &ec, sizeof ec) > 0) {
		int status;
		waitpid(pid, &status, 0);
		pid = -1;
		errno = ec;
	}
	close(p[0]);

out:
	if (pid > 0) *pm = m;
	else close(m);

	pthread_setcancelstate(cs, 0);
	pthread_sigmask(SIG_SETMASK, &oldset, 0);

	return pid;
}