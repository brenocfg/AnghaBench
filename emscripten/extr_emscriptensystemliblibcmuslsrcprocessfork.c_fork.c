#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
typedef  TYPE_2__* pthread_t ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_7__ {scalar_t__ threads_minus_1; } ;
struct TYPE_5__ {scalar_t__ pending; scalar_t__ off; } ;
struct TYPE_6__ {TYPE_1__ robust_list; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SYS_clone ; 
 int /*<<< orphan*/  SYS_gettid ; 
 int /*<<< orphan*/  __block_all_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __fork_handler (int) ; 
 TYPE_2__* __pthread_self () ; 
 int /*<<< orphan*/  __restore_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ) ; 
 TYPE_3__ libc ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

pid_t fork(void)
{
	pid_t ret;
	sigset_t set;
	__fork_handler(-1);
	__block_all_sigs(&set);
#ifdef SYS_fork
	ret = syscall(SYS_fork);
#else
	ret = syscall(SYS_clone, SIGCHLD, 0);
#endif
	if (!ret) {
		pthread_t self = __pthread_self();
		self->tid = __syscall(SYS_gettid);
		self->robust_list.off = 0;
		self->robust_list.pending = 0;
		libc.threads_minus_1 = 0;
	}
	__restore_sigs(&set);
	__fork_handler(!ret);
	return ret;
}