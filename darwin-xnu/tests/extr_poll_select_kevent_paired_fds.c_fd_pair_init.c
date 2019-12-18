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
typedef  enum fd_pair { ____Placeholder_fd_pair } fd_pair ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
#define  FIFO_PAIR 131 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
#define  PIPE_PAIR 130 
#define  PTY_PAIR 129 
#define  SOCKET_PAIR 128 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*,int) ; 
 int /*<<< orphan*/  T_ASSERT_NE (int,int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,...) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  mkfifo (char*,int) ; 
 int /*<<< orphan*/  mktemp (char*) ; 
 int open (char*,int) ; 
 int openpty (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pipe (int*) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
fd_pair_init(enum fd_pair fd_pair, int *rd_fd, int *wr_fd)
{
	switch (fd_pair) {
	case PTY_PAIR:
		T_ASSERT_POSIX_SUCCESS(openpty(rd_fd, wr_fd, NULL, NULL, NULL),
				NULL);
		break;

	case FIFO_PAIR: {
		char fifo_path[] = "/tmp/async-io-fifo.XXXXXX";
		T_QUIET; T_ASSERT_NOTNULL(mktemp(fifo_path), NULL);

		T_ASSERT_POSIX_SUCCESS(mkfifo(fifo_path, 0700), "mkfifo(%s, 0700)",
				fifo_path);
		/*
		 * Opening the read side of a pipe will block until the write
		 * side opens -- use O_NONBLOCK.
		 */
		*rd_fd = open(fifo_path, O_RDONLY | O_NONBLOCK);
		T_QUIET; T_ASSERT_POSIX_SUCCESS(*rd_fd, "open(... O_RDONLY)");
		*wr_fd = open(fifo_path, O_WRONLY | O_NONBLOCK);
		T_QUIET; T_ASSERT_POSIX_SUCCESS(*wr_fd, "open(... O_WRONLY)");
		break;
	}

	case PIPE_PAIR: {
		int pipe_fds[2];
		T_ASSERT_POSIX_SUCCESS(pipe(pipe_fds), NULL);
		*rd_fd = pipe_fds[0];
		*wr_fd = pipe_fds[1];
		break;
	}

	case SOCKET_PAIR: {
		int sock_fds[2];
		T_ASSERT_POSIX_SUCCESS(socketpair(AF_UNIX, SOCK_STREAM, 0, sock_fds),
				NULL);
		*rd_fd = sock_fds[0];
		*wr_fd = sock_fds[1];
		break;
	}

	default:
		T_ASSERT_FAIL("unknown descriptor pair type: %d", fd_pair);
		break;
	}

	T_QUIET; T_ASSERT_NE(*rd_fd, -1, "reading descriptor");
	T_QUIET; T_ASSERT_NE(*wr_fd, -1, "writing descriptor");
}