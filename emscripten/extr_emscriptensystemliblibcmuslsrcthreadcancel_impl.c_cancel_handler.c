#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  TYPE_2__* pthread_t ;
struct TYPE_5__ {int canceldisable; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; scalar_t__ cancelasync; int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 size_t CANCEL_REG_IP ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SYS_tgkill ; 
 int /*<<< orphan*/  __cancel () ; 
 TYPE_2__* __pthread_self () ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cancel_handler(int sig, siginfo_t *si, void *ctx)
{
	pthread_t self = __pthread_self();
	ucontext_t *uc = ctx;
	const char *ip = ((char **)&uc->uc_mcontext)[CANCEL_REG_IP];
	extern const char __cp_begin[1], __cp_end[1];

	if (!self->cancel || self->canceldisable) return;

	_sigaddset(&uc->uc_sigmask, SIGCANCEL);

	if (self->cancelasync || ip >= __cp_begin && ip < __cp_end) {
		self->canceldisable = 1;
		pthread_sigmask(SIG_SETMASK, &uc->uc_sigmask, 0);
		__cancel();
	}

	__syscall(SYS_tgkill, self->pid, self->tid, SIGCANCEL);
}