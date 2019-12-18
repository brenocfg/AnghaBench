#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct fown_struct {int /*<<< orphan*/  signum; } ;
struct TYPE_4__ {int si_signo; int si_code; long si_band; int si_fd; int /*<<< orphan*/  si_errno; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NSIGPOLL ; 
 int /*<<< orphan*/  POLL_IN ; 
 TYPE_1__* SEND_SIG_PRIV ; 
 int SIGIO ; 
 int __SI_MASK ; 
 int __SI_POLL ; 
 long* band_table ; 
 int /*<<< orphan*/  do_send_sig_info (int,TYPE_1__*,struct task_struct*,int) ; 
 int /*<<< orphan*/  sigio_perm (struct task_struct*,struct fown_struct*,int) ; 

__attribute__((used)) static void send_sigio_to_task(struct task_struct *p,
			       struct fown_struct *fown,
			       int fd, int reason, int group)
{
	/*
	 * F_SETSIG can change ->signum lockless in parallel, make
	 * sure we read it once and use the same value throughout.
	 */
	int signum = ACCESS_ONCE(fown->signum);

	if (!sigio_perm(p, fown, signum))
		return;

	switch (signum) {
		siginfo_t si;
		default:
			/* Queue a rt signal with the appropriate fd as its
			   value.  We use SI_SIGIO as the source, not 
			   SI_KERNEL, since kernel signals always get 
			   delivered even if we can't queue.  Failure to
			   queue in this case _should_ be reported; we fall
			   back to SIGIO in that case. --sct */
			si.si_signo = signum;
			si.si_errno = 0;
		        si.si_code  = reason;
			/* Make sure we are called with one of the POLL_*
			   reasons, otherwise we could leak kernel stack into
			   userspace.  */
			BUG_ON((reason & __SI_MASK) != __SI_POLL);
			if (reason - POLL_IN >= NSIGPOLL)
				si.si_band  = ~0L;
			else
				si.si_band = band_table[reason - POLL_IN];
			si.si_fd    = fd;
			if (!do_send_sig_info(signum, &si, p, group))
				break;
		/* fall-through: fall back on the old plain SIGIO signal */
		case 0:
			do_send_sig_info(SIGIO, SEND_SIG_PRIV, p, group);
	}
}