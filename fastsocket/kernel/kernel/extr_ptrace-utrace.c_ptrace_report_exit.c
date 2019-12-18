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
typedef  int /*<<< orphan*/  u32 ;
struct utrace_engine {int dummy; } ;
struct ptrace_context {long eventmsg; } ;
struct TYPE_2__ {int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_EVENT_EXIT ; 
 int /*<<< orphan*/  UTRACE_STOP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* current ; 
 struct ptrace_context* ptrace_context (struct utrace_engine*) ; 
 scalar_t__ ptrace_event_pending (struct ptrace_context*) ; 
 int /*<<< orphan*/  set_stop_code (struct ptrace_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_group_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ptrace_report_exit(u32 action, struct utrace_engine *engine,
			      long orig_code, long *code)
{
	struct ptrace_context *ctx = ptrace_context(engine);

	WARN_ON(ptrace_event_pending(ctx) &&
		!signal_group_exit(current->signal));

	set_stop_code(ctx, PTRACE_EVENT_EXIT);
	ctx->eventmsg = *code;

	return UTRACE_STOP;
}