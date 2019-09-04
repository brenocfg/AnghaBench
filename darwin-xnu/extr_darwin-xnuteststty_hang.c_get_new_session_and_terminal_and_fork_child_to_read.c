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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,int /*<<< orphan*/ *) ; 
 int close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  handle_sigttin ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setsid () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int tcsetpgrp (int,scalar_t__) ; 
 int write (int,char*,int) ; 

int
get_new_session_and_terminal_and_fork_child_to_read(char *pty_name)
{
	int sock_fd[2];
	int pty_fd;
	pid_t pid;
	char buf[10];

	/*
	 * We use this to handshake certain actions between this process and its
	 * child.
	 */
	T_ASSERT_POSIX_SUCCESS(socketpair(AF_UNIX, SOCK_STREAM, 0, sock_fd),
	   NULL);
	
	/*
	 * New session, lose any existing controlling terminal and become
	 * session leader.
	 */
	T_ASSERT_POSIX_SUCCESS(setsid(), NULL);
	
	/* now open pty, become controlling terminal of new session */
	T_ASSERT_POSIX_SUCCESS(pty_fd = open(pty_name, O_RDWR), NULL);
	
	T_ASSERT_POSIX_SUCCESS(pid = fork(), NULL);

	if (pid == 0) { /* child */
		int pty_fd_child;
		char buf[10];
		
		T_ASSERT_POSIX_SUCCESS(close(sock_fd[0]), NULL);
		T_ASSERT_POSIX_SUCCESS(close(pty_fd), NULL);

		/* Make a new process group for ourselves */
		T_ASSERT_POSIX_SUCCESS(setpgid(0, 0), NULL);

		T_ASSERT_POSIX_SUCCESS(pty_fd_child = open(pty_name, O_RDWR),
		    NULL);

		/* now let parent know we've done open and setpgid */
		write(sock_fd[1], "done", sizeof("done"));

		/* wait for parent to set us to the foreground process group */
		read(sock_fd[1], buf, sizeof(buf));

		/*
		 * We are the foreground process group now so we can read
		 * without getting a SIGTTIN.
		 *
		 * Once we are blocked though (we have a crude 1 second sleep on
		 * the parent to "detect" this), our parent is going to change
		 * us to be in the background.
		 *
		 * We'll be blocked until we get a signal and if that is signal
		 * is SIGTTIN, then the test has passed otherwise the test has
		 * failed.
		 */
		signal(SIGTTIN, handle_sigttin);
		(void)read(pty_fd_child, buf, sizeof(buf));
		/*
		 * If we get here, we passed, if we get any other signal than
		 * SIGTTIN, we will not reach here.
		 */
		exit(0);
	}
	
	T_ASSERT_POSIX_SUCCESS(close(sock_fd[1]), NULL);
	
	/* wait for child to open slave side and set its pgid to its pid */
	T_ASSERT_POSIX_SUCCESS(read(sock_fd[0], buf, sizeof(buf)), NULL);
	
	/*
	 * We need this to happen and in the order shown
	 *
	 * parent (pgid = pid)                  child (child_pgid = child_pid)
	 *
	 * 1 - tcsetpgrp(child_pgid)
	 * 2 -                                      block in read()
	 * 3 - tcsetpgrp(pgid)
	 *
	 * making sure 2 happens after 1 is easy, we use a sleep(1) in the
	 * parent to try and ensure 3 happens after 2.
	 */

	T_ASSERT_POSIX_SUCCESS(tcsetpgrp(pty_fd, pid), NULL);
	
	/* let child know you have set it to be the foreground process group */
	T_ASSERT_POSIX_SUCCESS(write(sock_fd[0], "done", sizeof("done")), NULL);
	
	/*
	 * give it a second to do the read of the terminal in response.
	 *
	 * XXX : Find a way to detect that the child is blocked in read(2).
	 */
	sleep(1);
	
	/*
	 * now change the foreground process group to ourselves -
	 * Note we are now in the background process group and we need to ignore
	 * SIGTTOU for this call to succeed.
	 *
	 * Hopefully the child has gotten to run and blocked for read on the
	 * terminal in the 1 second we slept.
	 */
	signal(SIGTTOU, SIG_IGN);
	T_ASSERT_POSIX_SUCCESS(tcsetpgrp(pty_fd, getpid()), NULL);

	return (0);
}