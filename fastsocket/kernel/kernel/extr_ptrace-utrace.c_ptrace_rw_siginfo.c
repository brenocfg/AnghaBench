#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct ptrace_context {int stop_code; TYPE_1__* siginfo; } ;
struct TYPE_4__ {int si_code; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int PTRACE_EVENT_MASK ; 
#define  PTRACE_EVENT_SIGNAL 128 
 int /*<<< orphan*/  SIGTRAP ; 
 int get_stop_event (struct ptrace_context*) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_is_traced (struct task_struct*) ; 
 int /*<<< orphan*/  task_pid_vnr (struct task_struct*) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static int ptrace_rw_siginfo(struct task_struct *tracee,
				struct ptrace_context *ctx,
				siginfo_t *info, bool write)
{
	unsigned long flags;
	int err;

	switch (get_stop_event(ctx)) {
	case 0: /* jctl stop */
		return -EINVAL;

	case PTRACE_EVENT_SIGNAL:
		err = -ESRCH;
		if (lock_task_sighand(tracee, &flags)) {
			if (likely(task_is_traced(tracee))) {
				if (write)
					*ctx->siginfo = *info;
				else
					*info = *ctx->siginfo;
				err = 0;
			}
			unlock_task_sighand(tracee, &flags);
		}

		return err;

	default:
		if (!write) {
			memset(info, 0, sizeof(*info));
			info->si_signo = SIGTRAP;
			info->si_code = ctx->stop_code & PTRACE_EVENT_MASK;
			info->si_pid = task_pid_vnr(tracee);
			info->si_uid = task_uid(tracee);
		}

		return 0;
	}
}