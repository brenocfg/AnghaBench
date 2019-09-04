#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct killpg1_iterargs {int signum; int /*<<< orphan*/  nfound; int /*<<< orphan*/  uc; int /*<<< orphan*/  curproc; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_6__ {int p_listflag; } ;

/* Variables and functions */
 int PROC_RETURNED ; 
 int P_LIST_EXITED ; 
 scalar_t__ cansignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ cansignal_nomac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  psignal (TYPE_1__*,int) ; 

__attribute__((used)) static int
killpg1_callback(proc_t p, void *arg)
{
	struct killpg1_iterargs *kargp = (struct killpg1_iterargs *)arg;
	int signum = kargp->signum;

	if ((p->p_listflag & P_LIST_EXITED) == P_LIST_EXITED) {
		/*
		 * Count zombies as found for the purposes of signalling, since POSIX
		 * 1003.1-2001 sees signalling zombies as successful.  If killpg(2) or
		 * kill(2) with pid -1 only finds zombies that can be signalled, it
		 * shouldn't return ESRCH.  See the Rationale for kill(2).
		 *
		 * Don't call into MAC -- it's not expecting signal checks for exited
		 * processes.
		 */
		if (cansignal_nomac(kargp->curproc, kargp->uc, p, signum)) {
			kargp->nfound++;
		}
	} else if (cansignal(kargp->curproc, kargp->uc, p, signum)) {
		kargp->nfound++;

		if (signum != 0) {
			psignal(p, signum);
		}
	}

	return PROC_RETURNED;
}