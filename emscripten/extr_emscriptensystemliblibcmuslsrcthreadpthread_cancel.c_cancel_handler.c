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
struct TYPE_5__ {uintptr_t MC_PC; } ;
struct TYPE_6__ {TYPE_1__ uc_mcontext; int /*<<< orphan*/  uc_sigmask; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  TYPE_3__* pthread_t ;
struct TYPE_7__ {scalar_t__ canceldisable; int /*<<< orphan*/  tid; scalar_t__ cancelasync; int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 scalar_t__ PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 int /*<<< orphan*/  SYS_tkill ; 
 scalar_t__ __cp_begin ; 
 scalar_t__ __cp_cancel ; 
 scalar_t__ __cp_end ; 
 TYPE_3__* __pthread_self () ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_barrier () ; 

__attribute__((used)) static void cancel_handler(int sig, siginfo_t *si, void *ctx)
{
	pthread_t self = __pthread_self();
	ucontext_t *uc = ctx;
	uintptr_t pc = uc->uc_mcontext.MC_PC;

	a_barrier();
	if (!self->cancel || self->canceldisable == PTHREAD_CANCEL_DISABLE) return;

	_sigaddset(&uc->uc_sigmask, SIGCANCEL);

	if (self->cancelasync || pc >= (uintptr_t)__cp_begin && pc < (uintptr_t)__cp_end) {
		uc->uc_mcontext.MC_PC = (uintptr_t)__cp_cancel;
		return;
	}

	__syscall(SYS_tkill, self->tid, SIGCANCEL);
}