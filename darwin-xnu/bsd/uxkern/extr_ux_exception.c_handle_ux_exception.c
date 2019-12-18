#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
typedef  scalar_t__ user_addr_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct sigacts {scalar_t__* ps_sigact; int ps_sigonstack; } ;
typedef  TYPE_2__* proc_t ;
typedef  void* mach_exception_subcode_t ;
typedef  int /*<<< orphan*/  mach_exception_code_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {scalar_t__ user_stack; int p_sigignore; int p_sigcatch; struct sigacts* p_sigacts; } ;
struct TYPE_6__ {int uu_sigwait; int uu_sigmask; int uu_exception; void* uu_subcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_PROTECTION_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MAXSSIZ ; 
 int SIGBUS ; 
 size_t SIGSEGV ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 TYPE_2__* proc_findthread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (TYPE_2__*) ; 
 int sigmask (int) ; 
 int /*<<< orphan*/  threadsignal (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ux_exception (int,int /*<<< orphan*/ ,void*) ; 

kern_return_t
handle_ux_exception(thread_t                    thread,
                    int                         exception,
                    mach_exception_code_t       code,
                    mach_exception_subcode_t    subcode)
{
	/* Returns +1 proc reference */
	proc_t p = proc_findthread(thread);

	/* Can't deliver a signal without a bsd process reference */
	if (p == NULL)
		return KERN_FAILURE;

	/* Translate exception and code to signal type */
	int ux_signal = ux_exception(exception, code, subcode);

	uthread_t ut = get_bsdthread_info(thread);

	/*
	 * Stack overflow should result in a SIGSEGV signal
	 * on the alternate stack.
	 * but we have one or more guard pages after the
	 * stack top, so we would get a KERN_PROTECTION_FAILURE
	 * exception instead of KERN_INVALID_ADDRESS, resulting in
	 * a SIGBUS signal.
	 * Detect that situation and select the correct signal.
	 */
	if (code == KERN_PROTECTION_FAILURE &&
	    ux_signal == SIGBUS) {
		user_addr_t sp = subcode;

		user_addr_t stack_max = p->user_stack;
		user_addr_t stack_min = p->user_stack - MAXSSIZ;
		if (sp >= stack_min && sp < stack_max) {
			/*
			 * This is indeed a stack overflow.  Deliver a
			 * SIGSEGV signal.
			 */
			ux_signal = SIGSEGV;

			/*
			 * If the thread/process is not ready to handle
			 * SIGSEGV on an alternate stack, force-deliver
			 * SIGSEGV with a SIG_DFL handler.
			 */
			int mask = sigmask(ux_signal);
			struct sigacts *ps = p->p_sigacts;
			if ((p->p_sigignore & mask) ||
			    (ut->uu_sigwait & mask) ||
			    (ut->uu_sigmask & mask) ||
			    (ps->ps_sigact[SIGSEGV] == SIG_IGN) ||
			    (! (ps->ps_sigonstack & mask))) {
				p->p_sigignore &= ~mask;
				p->p_sigcatch &= ~mask;
				ps->ps_sigact[SIGSEGV] = SIG_DFL;
				ut->uu_sigwait &= ~mask;
				ut->uu_sigmask &= ~mask;
			}
		}
	}

	/* Send signal to thread */
	if (ux_signal != 0) {
		ut->uu_exception = exception;
		//ut->uu_code = code; // filled in by threadsignal
		ut->uu_subcode = subcode;
		threadsignal(thread, ux_signal, code, TRUE);
	}

	proc_rele(p);

	return KERN_SUCCESS;
}