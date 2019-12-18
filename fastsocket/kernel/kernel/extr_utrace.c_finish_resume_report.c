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
struct utrace_report {int action; int /*<<< orphan*/  resume_action; } ;
struct utrace {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SIGPENDING ; 
#define  UTRACE_BLOCKSTEP 133 
#define  UTRACE_INTERRUPT 132 
#define  UTRACE_REPORT 131 
#define  UTRACE_RESUME 130 
#define  UTRACE_SINGLESTEP 129 
#define  UTRACE_STOP 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  arch_has_block_step () ; 
 int /*<<< orphan*/  arch_has_single_step () ; 
 int /*<<< orphan*/  finish_report_reset (struct task_struct*,struct utrace*,struct utrace_report*) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  user_disable_single_step (struct task_struct*) ; 
 int /*<<< orphan*/  user_enable_block_step (struct task_struct*) ; 
 int /*<<< orphan*/  user_enable_single_step (struct task_struct*) ; 
 int /*<<< orphan*/  utrace_stop (struct task_struct*,struct utrace*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finish_resume_report(struct task_struct *task,
				 struct utrace *utrace,
				 struct utrace_report *report)
{
	finish_report_reset(task, utrace, report);

	switch (report->action) {
	case UTRACE_STOP:
		utrace_stop(task, utrace, report->resume_action);
		break;

	case UTRACE_INTERRUPT:
		if (!signal_pending(task))
			set_tsk_thread_flag(task, TIF_SIGPENDING);
		break;

	case UTRACE_BLOCKSTEP:
		if (likely(arch_has_block_step())) {
			user_enable_block_step(task);
			break;
		}

		/*
		 * This means some callback is to blame for failing
		 * to check arch_has_block_step() itself.  Warn and
		 * then fall through to treat it as SINGLESTEP.
		 */
		WARN(1, "UTRACE_BLOCKSTEP when !arch_has_block_step()");

	case UTRACE_SINGLESTEP:
		if (likely(arch_has_single_step())) {
			user_enable_single_step(task);
		} else {
			/*
			 * This means some callback is to blame for failing
			 * to check arch_has_single_step() itself.  Spew
			 * about it so the loser will fix his module.
			 */
			WARN(1,
			     "UTRACE_SINGLESTEP when !arch_has_single_step()");
		}
		break;

	case UTRACE_REPORT:
	case UTRACE_RESUME:
	default:
		user_disable_single_step(task);
		break;
	}
}