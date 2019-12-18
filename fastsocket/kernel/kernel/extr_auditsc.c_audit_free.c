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
struct task_struct {int dummy; } ;
struct audit_context {scalar_t__ current_state; int /*<<< orphan*/  killed_trees; scalar_t__ in_syscall; } ;

/* Variables and functions */
 scalar_t__ AUDIT_RECORD_CONTEXT ; 
 int /*<<< orphan*/  audit_free_context (struct audit_context*) ; 
 struct audit_context* audit_get_context (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_kill_trees (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_exit (struct audit_context*,struct task_struct*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void audit_free(struct task_struct *tsk)
{
	struct audit_context *context;

	context = audit_get_context(tsk, 0, 0);
	if (likely(!context))
		return;

	/* Check for system calls that do not go through the exit
	 * function (e.g., exit_group), then free context block.
	 * We use GFP_ATOMIC here because we might be doing this
	 * in the context of the idle thread */
	/* that can happen only if we are called from do_exit() */
	if (context->in_syscall && context->current_state == AUDIT_RECORD_CONTEXT)
		audit_log_exit(context, tsk);
	if (!list_empty(&context->killed_trees))
		audit_kill_trees(&context->killed_trees);

	audit_free_context(context);
}