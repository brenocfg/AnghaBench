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
struct pt_regs {int /*<<< orphan*/  ar_bspstore; } ;

/* Variables and functions */
 unsigned long ia64_get_user_rbs_end (struct task_struct*,struct pt_regs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_kernel_rbs (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ ptrace_check_attach (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

__attribute__((used)) static inline int
thread_matches (struct task_struct *thread, unsigned long addr)
{
	unsigned long thread_rbs_end;
	struct pt_regs *thread_regs;

	if (ptrace_check_attach(thread, 0) < 0)
		/*
		 * If the thread is not in an attachable state, we'll
		 * ignore it.  The net effect is that if ADDR happens
		 * to overlap with the portion of the thread's
		 * register backing store that is currently residing
		 * on the thread's kernel stack, then ptrace() may end
		 * up accessing a stale value.  But if the thread
		 * isn't stopped, that's a problem anyhow, so we're
		 * doing as well as we can...
		 */
		return 0;

	thread_regs = task_pt_regs(thread);
	thread_rbs_end = ia64_get_user_rbs_end(thread, thread_regs, NULL);
	if (!on_kernel_rbs(addr, thread_regs->ar_bspstore, thread_rbs_end))
		return 0;

	return 1;	/* looks like we've got a winner */
}