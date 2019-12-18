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
typedef  int /*<<< orphan*/  uid_t ;
struct task_struct {unsigned int sessionid; int /*<<< orphan*/  loginuid; int /*<<< orphan*/  pid; struct audit_context* audit_context; } ;
struct audit_context {scalar_t__ in_syscall; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_LOGIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_task_context (struct audit_buffer*) ; 
 int /*<<< orphan*/  session_id ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 

int audit_set_loginuid(struct task_struct *task, uid_t loginuid)
{
	unsigned int sessionid = atomic_inc_return(&session_id);
	struct audit_context *context = task->audit_context;

	if (context && context->in_syscall) {
		struct audit_buffer *ab;

		ab = audit_log_start(NULL, GFP_KERNEL, AUDIT_LOGIN);
		if (ab) {
			audit_log_format(ab, "pid=%d uid=%u", task->pid,
					 task_uid(task));
			audit_log_task_context(ab);
			audit_log_format(ab, " old auid=%u new auid=%u "
					 "old ses=%u new ses=%u",
					 task->loginuid, loginuid,
					 task->sessionid, sessionid);
			audit_log_end(ab);
		}
	}
	task->sessionid = sessionid;
	task->loginuid = loginuid;
	return 0;
}