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
typedef  enum write_mode { ____Placeholder_write_mode } write_mode ;
typedef  enum read_mode { ____Placeholder_read_mode } read_mode ;
typedef  enum fd_pair { ____Placeholder_fd_pair } fd_pair ;
typedef  int /*<<< orphan*/  dt_helper_t ;
struct TYPE_3__ {int out_fd; int in_fd; } ;
struct TYPE_4__ {int fd_pair; int rd_mode; int wr_mode; int /*<<< orphan*/  wr_fd; int /*<<< orphan*/  rd_fd; TYPE_1__ wr_wait; int /*<<< orphan*/  wr_kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESS_WRITER ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_fork_helper (char*) ; 
 int /*<<< orphan*/  dt_run_helpers (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fd_pair_init (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe (int*) ; 
 TYPE_2__ shared ; 

__attribute__((used)) static void __attribute__((noreturn))
drive_processes(enum fd_pair fd_pair, enum read_mode rd_mode, enum write_mode wr_mode)
{
	shared.fd_pair = fd_pair;
	shared.rd_mode = rd_mode;
	shared.wr_mode = wr_mode;
	fd_pair_init(fd_pair, &(shared.rd_fd), &(shared.wr_fd));

	shared.wr_kind = PROCESS_WRITER;
	int fds[2];
	T_QUIET; T_ASSERT_POSIX_SUCCESS(pipe(fds), NULL);
	shared.wr_wait.out_fd = fds[0];
	shared.wr_wait.in_fd = fds[1];

	T_LOG("starting subprocesses");
	dt_helper_t helpers[2] = {
		dt_fork_helper("reader_helper"),
		dt_fork_helper("writer_helper")
	};

	close(shared.rd_fd);
	close(shared.wr_fd);

	dt_run_helpers(helpers, 2, 50000);
}