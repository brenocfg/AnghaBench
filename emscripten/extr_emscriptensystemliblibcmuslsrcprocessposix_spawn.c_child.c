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
struct sigaction {scalar_t__ sa_handler; int /*<<< orphan*/  member_0; } ;
struct fdop {int fd; int cmd; int srcfd; int /*<<< orphan*/  mode; int /*<<< orphan*/  oflag; int /*<<< orphan*/  path; struct fdop* prev; struct fdop* next; } ;
struct args {int* p; int /*<<< orphan*/  envp; int /*<<< orphan*/  argv; int /*<<< orphan*/  path; int /*<<< orphan*/  (* exec ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  oldmask; TYPE_1__* attr; TYPE_2__* fa; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_3__ {int __flags; int /*<<< orphan*/  __mask; int /*<<< orphan*/  __pgrp; int /*<<< orphan*/  __def; } ;
typedef  TYPE_1__ posix_spawnattr_t ;
struct TYPE_4__ {struct fdop* __actions; } ;
typedef  TYPE_2__ posix_spawn_file_actions_t ;

/* Variables and functions */
#define  FDOP_CLOSE 130 
#define  FDOP_DUP2 129 
#define  FDOP_OPEN 128 
 int FD_CLOEXEC ; 
 int* F_SETFD ; 
 int POSIX_SPAWN_RESETIDS ; 
 int POSIX_SPAWN_SETPGROUP ; 
 int POSIX_SPAWN_SETSIGDEF ; 
 int POSIX_SPAWN_SETSIGMASK ; 
 void* SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  SYS_dup ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  SYS_getgid ; 
 int /*<<< orphan*/  SYS_getuid ; 
 int /*<<< orphan*/  SYS_setgid ; 
 int /*<<< orphan*/  SYS_setpgid ; 
 int /*<<< orphan*/  SYS_setuid ; 
 int /*<<< orphan*/  SYS_write ; 
 int _NSIG ; 
 int /*<<< orphan*/  __get_handler_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __libc_sigaction (int,struct sigaction*,struct sigaction*) ; 
 int __sys_dup2 (int,int) ; 
 int __sys_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __syscall (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int child(void *args_vp)
{
	int i, ret;
	struct sigaction sa = {0};
	struct args *args = args_vp;
	int p = args->p[1];
	const posix_spawn_file_actions_t *fa = args->fa;
	const posix_spawnattr_t *restrict attr = args->attr;
	sigset_t hset;

	close(args->p[0]);

	/* All signal dispositions must be either SIG_DFL or SIG_IGN
	 * before signals are unblocked. Otherwise a signal handler
	 * from the parent might get run in the child while sharing
	 * memory, with unpredictable and dangerous results. To
	 * reduce overhead, sigaction has tracked for us which signals
	 * potentially have a signal handler. */
	__get_handler_set(&hset);
	for (i=1; i<_NSIG; i++) {
		if ((attr->__flags & POSIX_SPAWN_SETSIGDEF)
		     && sigismember(&attr->__def, i)) {
			sa.sa_handler = SIG_DFL;
		} else if (sigismember(&hset, i)) {
			if (i-32<3U) {
				sa.sa_handler = SIG_IGN;
			} else {
				__libc_sigaction(i, 0, &sa);
				if (sa.sa_handler==SIG_IGN) continue;
				sa.sa_handler = SIG_DFL;
			}
		} else {
			continue;
		}
		__libc_sigaction(i, &sa, 0);
	}

	if (attr->__flags & POSIX_SPAWN_SETPGROUP)
		if ((ret=__syscall(SYS_setpgid, 0, attr->__pgrp)))
			goto fail;

	/* Use syscalls directly because the library functions attempt
	 * to do a multi-threaded synchronized id-change, which would
	 * trash the parent's state. */
	if (attr->__flags & POSIX_SPAWN_RESETIDS)
		if ((ret=__syscall(SYS_setgid, __syscall(SYS_getgid))) ||
		    (ret=__syscall(SYS_setuid, __syscall(SYS_getuid))) )
			goto fail;

	if (fa && fa->__actions) {
		struct fdop *op;
		int fd;
		for (op = fa->__actions; op->next; op = op->next);
		for (; op; op = op->prev) {
			/* It's possible that a file operation would clobber
			 * the pipe fd used for synchronizing with the
			 * parent. To avoid that, we dup the pipe onto
			 * an unoccupied fd. */
			if (op->fd == p) {
				ret = __syscall(SYS_dup, p);
				if (ret < 0) goto fail;
				__syscall(SYS_close, p);
				p = ret;
			}
			switch(op->cmd) {
			case FDOP_CLOSE:
				__syscall(SYS_close, op->fd);
				break;
			case FDOP_DUP2:
				if ((ret=__sys_dup2(op->srcfd, op->fd))<0)
					goto fail;
				break;
			case FDOP_OPEN:
				fd = __sys_open(op->path, op->oflag, op->mode);
				if ((ret=fd) < 0) goto fail;
				if (fd != op->fd) {
					if ((ret=__sys_dup2(fd, op->fd))<0)
						goto fail;
					__syscall(SYS_close, fd);
				}
				break;
			}
		}
	}

	/* Close-on-exec flag may have been lost if we moved the pipe
	 * to a different fd. We don't use F_DUPFD_CLOEXEC above because
	 * it would fail on older kernels and atomicity is not needed --
	 * in this process there are no threads or signal handlers. */
	__syscall(SYS_fcntl, p, F_SETFD, FD_CLOEXEC);

	pthread_sigmask(SIG_SETMASK, (attr->__flags & POSIX_SPAWN_SETSIGMASK)
		? &attr->__mask : &args->oldmask, 0);

	args->exec(args->path, args->argv, args->envp);
	ret = -errno;

fail:
	/* Since sizeof errno < PIPE_BUF, the write is atomic. */
	ret = -ret;
	if (ret) while (__syscall(SYS_write, p, &ret, sizeof ret) < 0);
	_exit(127);
}