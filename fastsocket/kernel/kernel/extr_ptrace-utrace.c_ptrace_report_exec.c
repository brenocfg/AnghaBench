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
typedef  int /*<<< orphan*/  u32 ;
struct utrace_engine {int dummy; } ;
struct ptrace_context {int options; } ;
struct pt_regs {int dummy; } ;
struct linux_binprm {int dummy; } ;
struct linux_binfmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_EVENT_EXEC ; 
 int PTRACE_O_TRACEEXEC ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  UTRACE_RESUME ; 
 int /*<<< orphan*/  UTRACE_STOP ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct ptrace_context* ptrace_context (struct utrace_engine*) ; 
 int /*<<< orphan*/  ptrace_event_pending (struct ptrace_context*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_stop_code (struct ptrace_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ptrace_report_exec(u32 action, struct utrace_engine *engine,
			      const struct linux_binfmt *fmt,
			      const struct linux_binprm *bprm,
			      struct pt_regs *regs)
{
	struct ptrace_context *ctx = ptrace_context(engine);

	WARN_ON(ptrace_event_pending(ctx));

	if (!(ctx->options & PTRACE_O_TRACEEXEC)) {
		/*
		 * Old-fashioned ptrace'd exec just posts a plain signal.
		 */
		send_sig(SIGTRAP, current, 0);
		return UTRACE_RESUME;
	}

	set_stop_code(ctx, PTRACE_EVENT_EXEC);
	return UTRACE_STOP;
}