#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
struct TYPE_2__ {int detached; int /*<<< orphan*/  start_arg; int /*<<< orphan*/  (* start ) (int /*<<< orphan*/ ) ;scalar_t__ unblock_cancel; int /*<<< orphan*/  sigmask; scalar_t__* startlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPT_SET ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  SYS_rt_sigprocmask ; 
 int _NSIG ; 
 int /*<<< orphan*/  __pthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __restore_sigs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __wait (scalar_t__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start(void *p)
{
	pthread_t self = p;
	if (self->startlock[0]) {
		__wait(self->startlock, 0, 1, 1);
		if (self->startlock[0]) {
			self->detached = 2;
			pthread_exit(0);
		}
		__restore_sigs(self->sigmask);
	}
	if (self->unblock_cancel)
		__syscall(SYS_rt_sigprocmask, SIG_UNBLOCK,
			SIGPT_SET, 0, _NSIG/8);
	__pthread_exit(self->start(self->start_arg));
	return 0;
}