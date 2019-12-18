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
struct task_struct {struct audit_context* audit_context; } ;
struct audit_context {scalar_t__ current_state; unsigned long long prio; scalar_t__ state; int* fds; int /*<<< orphan*/ * filterkey; scalar_t__ type; scalar_t__ sockaddr_len; scalar_t__ target_sid; scalar_t__ target_pid; int /*<<< orphan*/ * aux_pids; int /*<<< orphan*/ * aux; struct audit_context* previous; int /*<<< orphan*/  killed_trees; scalar_t__ in_syscall; } ;

/* Variables and functions */
 int AUDITSC_FAILURE ; 
 int AUDITSC_SUCCESS ; 
 scalar_t__ AUDIT_RECORD_CONTEXT ; 
 int /*<<< orphan*/  audit_free_aux (struct audit_context*) ; 
 int /*<<< orphan*/  audit_free_context (struct audit_context*) ; 
 int /*<<< orphan*/  audit_free_names (struct audit_context*) ; 
 struct audit_context* audit_get_context (struct task_struct*,int,long) ; 
 int /*<<< orphan*/  audit_kill_trees (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_exit (struct audit_context*,struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unroll_tree_refs (struct audit_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __audit_syscall_exit(int success, long return_code)
{
	struct task_struct *tsk = current;
	struct audit_context *context;

	if (success)
		success = AUDITSC_SUCCESS;
	else
		success = AUDITSC_FAILURE;

	context = audit_get_context(tsk, success, return_code);
	if (likely(!context))
		return;

	if (context->in_syscall && context->current_state == AUDIT_RECORD_CONTEXT)
		audit_log_exit(context, tsk);

	context->in_syscall = 0;
	context->prio = context->state == AUDIT_RECORD_CONTEXT ? ~0ULL : 0;

	if (!list_empty(&context->killed_trees))
		audit_kill_trees(&context->killed_trees);

	if (context->previous) {
		struct audit_context *new_context = context->previous;
		context->previous  = NULL;
		audit_free_context(context);
		tsk->audit_context = new_context;
	} else {
		audit_free_names(context);
		unroll_tree_refs(context, NULL, 0);
		audit_free_aux(context);
		context->aux = NULL;
		context->aux_pids = NULL;
		context->target_pid = 0;
		context->target_sid = 0;
		context->sockaddr_len = 0;
		context->type = 0;
		context->fds[0] = -1;
		if (context->state != AUDIT_RECORD_CONTEXT) {
			kfree(context->filterkey);
			context->filterkey = NULL;
		}
		tsk->audit_context = context;
	}
}