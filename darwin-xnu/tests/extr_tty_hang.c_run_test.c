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
 int /*<<< orphan*/  F_SETFL ; 
 int O_NOCTTY ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_FAIL (char*,int) ; 
 int /*<<< orphan*/  T_LOG (char*,char*) ; 
 int /*<<< orphan*/  T_PASS (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SETUPBEGIN ; 
 int /*<<< orphan*/  T_SETUPEND ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  dt_waitpid (scalar_t__,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  get_new_session_and_terminal_and_fork_child_to_read (char*) ; 
 scalar_t__ grantpt (int) ; 
 int posix_openpt (int) ; 
 char* ptsname (int) ; 
 scalar_t__ revoke (char*) ; 
 int strsignal (int) ; 
 scalar_t__ unlockpt (int) ; 

void
run_test(int do_revoke)
{
	int master_fd;
	char *slave_pty;
	pid_t pid;

	T_WITH_ERRNO;
	T_QUIET;

	T_SETUPBEGIN;
	
	slave_pty= NULL;
	T_ASSERT_POSIX_SUCCESS(master_fd = posix_openpt(O_RDWR | O_NOCTTY),
	    NULL);
	(void)fcntl(master_fd, F_SETFL, O_NONBLOCK);
	T_ASSERT_POSIX_SUCCESS(grantpt(master_fd), NULL);
	T_ASSERT_POSIX_SUCCESS(unlockpt(master_fd), NULL);
	slave_pty= ptsname(master_fd);
	T_ASSERT_NOTNULL(slave_pty, NULL);
	T_LOG("slave pty is %s\n", slave_pty);

	T_SETUPEND;
	
	/*
	 * We get the stdin and stdout redirection but we don't have visibility
	 * into the child (nor can we wait for it). To get around that, we fork
	 * and only let the parent to the caller and the child exits before
	 * returning to the caller.
	 */
	T_ASSERT_POSIX_SUCCESS(pid = fork(), NULL);
	
	if (pid == 0) { /* child */
		T_ASSERT_POSIX_SUCCESS(close(master_fd), NULL);
		get_new_session_and_terminal_and_fork_child_to_read(slave_pty);

		/*
		 * These tests are for testing revoke and read hangs. This
		 * revoke can be explicit by a revoke(2) system call (test 2)
		 * or as part of exit(2) of the session leader (test 1).
		 * The exit hang is the common hang and can be fixed
		 * independently but fixing the revoke(2) hang requires us make
		 * changes in the tcsetpgrp path ( which also fixes the exit
		 * hang). In essence, we have 2 fixes. One which only addresses
		 * the exit hang and one which fixes both.
		 */
		if (do_revoke) {
			/* This should not hang for the test to pass .. */
			T_ASSERT_POSIX_SUCCESS(revoke(slave_pty), NULL);
		}
		/*
		 * This child has the same dt_helper variables as its parent
		 * The way dt_fork_helpers work if we don't exit() from here,
		 * we will be killing the parent. So we have to exit() and not
		 * let the dt_fork_helpers continue.
		 * If we didn't do the revoke(2), This test passes if this exit
		 * doesn't hang waiting for its child to finish reading.
		 */
		exit(0);
	}

	int status;
	int sig;

	dt_waitpid(pid, &status, &sig, 0);
	if (sig) {
		T_FAIL("Test failed because child received signal %s\n",
		       strsignal(sig));
	} else if (status) {
		T_FAIL("Test failed because child exited with status %d\n",
		       status);
	} else {
		T_PASS("test_passed\n");
	}
	/*
	 * we can let this process proceed with the regular darwintest process
	 * termination and cleanup.
	 */
}