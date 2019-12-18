#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct utrace_engine {int dummy; } ;
struct task_struct {int dummy; } ;
struct ptrace_context {int resume; int signr; int /*<<< orphan*/  options; scalar_t__ siginfo; } ;
typedef  enum utrace_resume_action { ____Placeholder_utrace_resume_action } utrace_resume_action ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct utrace_engine*) ; 
#define  PTRACE_EVENT_SIGNAL 129 
#define  PTRACE_EVENT_SYSCALL 128 
 int /*<<< orphan*/  PTRACE_O_DETACHED ; 
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int UTRACE_DETACH ; 
 int UTRACE_RESUME ; 
 int get_stop_event (struct ptrace_context*) ; 
 struct ptrace_context* ptrace_context (struct utrace_engine*) ; 
 struct utrace_engine* ptrace_lookup_engine (struct task_struct*) ; 
 int /*<<< orphan*/  ptrace_wake_up (struct task_struct*,struct utrace_engine*,int,int) ; 
 int /*<<< orphan*/  send_sig_info (int,int /*<<< orphan*/ ,struct task_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int utrace_barrier_uninterruptible (struct task_struct*,struct utrace_engine*) ; 
 int /*<<< orphan*/  utrace_engine_put (struct utrace_engine*) ; 

__attribute__((used)) static void ptrace_detach_task(struct task_struct *tracee, int sig)
{
	/*
	 * If true, the caller is PTRACE_DETACH, otherwise
	 * the tracer detaches implicitly during exit.
	 */
	bool explicit = (sig >= 0);
	struct utrace_engine *engine = ptrace_lookup_engine(tracee);
	enum utrace_resume_action action = UTRACE_DETACH;
	struct ptrace_context *ctx;

	if (unlikely(IS_ERR(engine)))
		return;

	ctx = ptrace_context(engine);

	if (!explicit) {
		int err;

		/*
		 * We are going to detach, the tracee can be running.
		 * Ensure ptrace_report_signal() won't report a signal.
		 */
		ctx->resume = UTRACE_DETACH;
		err = utrace_barrier_uninterruptible(tracee, engine);

		if (!err && ctx->siginfo) {
			/*
			 * The tracee has already reported a signal
			 * before utrace_barrier().
			 *
			 * Resume it like we do in PTRACE_EVENT_SIGNAL
			 * case below. The difference is that we can race
			 * with ptrace_report_signal() if the tracee is
			 * running but this doesn't matter. In any case
			 * UTRACE_SIGNAL_REPORT must be pending and it
			 * can return nothing but UTRACE_DETACH.
			 */
			action = UTRACE_RESUME;
		}

	} else if (sig) {
		switch (get_stop_event(ctx)) {
		case PTRACE_EVENT_SYSCALL:
			send_sig_info(sig, SEND_SIG_PRIV, tracee);
			break;

		case PTRACE_EVENT_SIGNAL:
			ctx->signr = sig;
			ctx->resume = UTRACE_DETACH;
			action = UTRACE_RESUME;
			break;
		}
	}

	ptrace_wake_up(tracee, engine, action, explicit);

	if (action != UTRACE_DETACH)
		ctx->options = PTRACE_O_DETACHED;

	utrace_engine_put(engine);
}