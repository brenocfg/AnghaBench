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
struct ptrace_context {int /*<<< orphan*/  resume; } ;

/* Variables and functions */
 int /*<<< orphan*/  UTRACE_RESUME ; 
 int /*<<< orphan*/  UTRACE_STOP ; 
 struct ptrace_context* ptrace_context (struct utrace_engine*) ; 
 scalar_t__ ptrace_event_pending (struct ptrace_context*) ; 

__attribute__((used)) static u32 ptrace_report_quiesce(u32 action, struct utrace_engine *engine,
				 unsigned long event)
{
	struct ptrace_context *ctx = ptrace_context(engine);

	if (ptrace_event_pending(ctx))
		return UTRACE_STOP;

	return event ? UTRACE_RESUME : ctx->resume;
}