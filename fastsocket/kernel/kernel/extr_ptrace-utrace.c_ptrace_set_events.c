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
struct ptrace_context {unsigned long options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE ; 
 int /*<<< orphan*/  EXEC ; 
 int /*<<< orphan*/  EXIT ; 
 unsigned long PTRACE_O_TRACEEXIT ; 
 int /*<<< orphan*/  QUIESCE ; 
 unsigned long UTRACE_EVENT (int /*<<< orphan*/ ) ; 
 unsigned long UTRACE_EVENT_SIGNAL_ALL ; 
 struct ptrace_context* ptrace_context (struct utrace_engine*) ; 
 int utrace_set_events (struct task_struct*,struct utrace_engine*,unsigned long) ; 

__attribute__((used)) static inline int ptrace_set_events(struct task_struct *target,
					struct utrace_engine *engine,
					unsigned long options)
{
	struct ptrace_context *ctx = ptrace_context(engine);
	/*
	 * We need QUIESCE for resume handling, CLONE to check
	 * for CLONE_PTRACE, other events are always reported.
	 */
	unsigned long events = UTRACE_EVENT(QUIESCE) | UTRACE_EVENT(CLONE) |
			       UTRACE_EVENT(EXEC) | UTRACE_EVENT_SIGNAL_ALL;

	ctx->options = options;
	if (options & PTRACE_O_TRACEEXIT)
		events |= UTRACE_EVENT(EXIT);

	return utrace_set_events(target, engine, events);
}