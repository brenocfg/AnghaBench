#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {long r8; long r1; int cr_iip; int /*<<< orphan*/  r15; scalar_t__ r10; } ;
struct sigscratch {TYPE_2__ pt; } ;
struct TYPE_8__ {int sa_flags; } ;
struct k_sigaction {TYPE_1__ sa; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_11__ {int /*<<< orphan*/  saved_sigmask; int /*<<< orphan*/  blocked; } ;
struct TYPE_10__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
#define  ERESTARTNOHAND 131 
#define  ERESTARTNOINTR 130 
#define  ERESTARTSYS 129 
#define  ERESTART_RESTARTBLOCK 128 
 void* ERR_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_IA32_PROCESS (TYPE_2__*) ; 
 int SA_RESTART ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int TS_RESTORE_SIGMASK ; 
 int /*<<< orphan*/  __NR_restart_syscall ; 
 TYPE_6__* current ; 
 TYPE_5__* current_thread_info () ; 
 int get_signal_to_deliver (int /*<<< orphan*/ *,struct k_sigaction*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ handle_signal (int,struct k_sigaction*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sigscratch*) ; 
 int /*<<< orphan*/  ia64_decrement_ip (TYPE_2__*) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (long) ; 
 int /*<<< orphan*/  user_mode (TYPE_2__*) ; 

void
ia64_do_signal (struct sigscratch *scr, long in_syscall)
{
	struct k_sigaction ka;
	sigset_t *oldset;
	siginfo_t info;
	long restart = in_syscall;
	long errno = scr->pt.r8;
#	define ERR_CODE(c)	(IS_IA32_PROCESS(&scr->pt) ? -(c) : (c))

	/*
	 * In the ia64_leave_kernel code path, we want the common case to go fast, which
	 * is why we may in certain cases get here from kernel mode. Just return without
	 * doing anything if so.
	 */
	if (!user_mode(&scr->pt))
		return;

	if (current_thread_info()->status & TS_RESTORE_SIGMASK)
		oldset = &current->saved_sigmask;
	else
		oldset = &current->blocked;

	/*
	 * This only loops in the rare cases of handle_signal() failing, in which case we
	 * need to push through a forced SIGSEGV.
	 */
	while (1) {
		int signr = get_signal_to_deliver(&info, &ka, &scr->pt, NULL);

		/*
		 * get_signal_to_deliver() may have run a debugger (via notify_parent())
		 * and the debugger may have modified the state (e.g., to arrange for an
		 * inferior call), thus it's important to check for restarting _after_
		 * get_signal_to_deliver().
		 */
		if (IS_IA32_PROCESS(&scr->pt)) {
			if (in_syscall) {
				if (errno >= 0)
					restart = 0;
				else
					errno = -errno;
			}
		} else if ((long) scr->pt.r10 != -1)
			/*
			 * A system calls has to be restarted only if one of the error codes
			 * ERESTARTNOHAND, ERESTARTSYS, or ERESTARTNOINTR is returned.  If r10
			 * isn't -1 then r8 doesn't hold an error code and we don't need to
			 * restart the syscall, so we can clear the "restart" flag here.
			 */
			restart = 0;

		if (signr <= 0)
			break;

		if (unlikely(restart)) {
			switch (errno) {
			      case ERESTART_RESTARTBLOCK:
			      case ERESTARTNOHAND:
				scr->pt.r8 = ERR_CODE(EINTR);
				/* note: scr->pt.r10 is already -1 */
				break;

			      case ERESTARTSYS:
				if ((ka.sa.sa_flags & SA_RESTART) == 0) {
					scr->pt.r8 = ERR_CODE(EINTR);
					/* note: scr->pt.r10 is already -1 */
					break;
				}
			      case ERESTARTNOINTR:
				if (IS_IA32_PROCESS(&scr->pt)) {
					scr->pt.r8 = scr->pt.r1;
					scr->pt.cr_iip -= 2;
				} else
					ia64_decrement_ip(&scr->pt);
				restart = 0; /* don't restart twice if handle_signal() fails... */
			}
		}

		/*
		 * Whee!  Actually deliver the signal.  If the delivery failed, we need to
		 * continue to iterate in this loop so we can deliver the SIGSEGV...
		 */
		if (handle_signal(signr, &ka, &info, oldset, scr)) {
			/*
			 * A signal was successfully delivered; the saved
			 * sigmask will have been stored in the signal frame,
			 * and will be restored by sigreturn, so we can simply
			 * clear the TS_RESTORE_SIGMASK flag.
			 */
			current_thread_info()->status &= ~TS_RESTORE_SIGMASK;
			return;
		}
	}

	/* Did we come from a system call? */
	if (restart) {
		/* Restart the system call - no handlers present */
		if (errno == ERESTARTNOHAND || errno == ERESTARTSYS || errno == ERESTARTNOINTR
		    || errno == ERESTART_RESTARTBLOCK)
		{
			if (IS_IA32_PROCESS(&scr->pt)) {
				scr->pt.r8 = scr->pt.r1;
				scr->pt.cr_iip -= 2;
				if (errno == ERESTART_RESTARTBLOCK)
					scr->pt.r8 = 0;	/* x86 version of __NR_restart_syscall */
			} else {
				/*
				 * Note: the syscall number is in r15 which is saved in
				 * pt_regs so all we need to do here is adjust ip so that
				 * the "break" instruction gets re-executed.
				 */
				ia64_decrement_ip(&scr->pt);
				if (errno == ERESTART_RESTARTBLOCK)
					scr->pt.r15 = __NR_restart_syscall;
			}
		}
	}

	/* if there's no signal to deliver, we just put the saved sigmask
	 * back */
	if (current_thread_info()->status & TS_RESTORE_SIGMASK) {
		current_thread_info()->status &= ~TS_RESTORE_SIGMASK;
		sigprocmask(SIG_SETMASK, &current->saved_sigmask, NULL);
	}
}