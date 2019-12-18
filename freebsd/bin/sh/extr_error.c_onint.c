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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXINT ; 
 scalar_t__ SIGINT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  _exit (scalar_t__) ; 
 int /*<<< orphan*/  exraise (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 scalar_t__ iflag ; 
 scalar_t__ intpending ; 
 int /*<<< orphan*/  kill (scalar_t__,scalar_t__) ; 
 scalar_t__ rootshell ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

void
onint(void)
{
	sigset_t sigs;

	intpending = 0;
	sigemptyset(&sigs);
	sigprocmask(SIG_SETMASK, &sigs, NULL);

	/*
	 * This doesn't seem to be needed, since main() emits a newline.
	 */
#if 0
	if (tcgetpgrp(0) == getpid())
		write(STDERR_FILENO, "\n", 1);
#endif
	if (rootshell && iflag)
		exraise(EXINT);
	else {
		signal(SIGINT, SIG_DFL);
		kill(getpid(), SIGINT);
		_exit(128 + SIGINT);
	}
}