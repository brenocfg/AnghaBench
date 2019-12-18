#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {int uu_siglist; int uu_sigmask; } ;
typedef  int sigset_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {int p_sigignore; } ;

/* Variables and functions */
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

int
thread_issignal(proc_t p, thread_t th, sigset_t mask)
{
	struct uthread * uth;
	sigset_t  bits=0;

	proc_lock(p);
	uth = (struct uthread *)get_bsdthread_info(th);
	if (uth) {
		bits = (((uth->uu_siglist & ~uth->uu_sigmask) & ~p->p_sigignore) & mask);
	}
	proc_unlock(p);
	return(bits);
}