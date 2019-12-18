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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TIMEOUT_SECS ; 
 int /*<<< orphan*/  child_tty_client () ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int setpgid (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int tcsetpgrp (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
pty_master(void)
{
	pid_t child_pid;
	int ret;

	child_pid = fork();
	if (child_pid == 0) {
		child_tty_client();
	}
	ret = setpgid(child_pid, child_pid);
	if (ret < 0) {
		exit(1);
	}
	ret = tcsetpgrp(STDIN_FILENO, child_pid);
	if (ret < 0) {
		exit(1);
	}

	sleep(TIMEOUT_SECS);
	exit(1);
}