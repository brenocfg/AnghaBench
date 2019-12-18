#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct stacktrace_ops {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dump ) (struct task_struct*,struct pt_regs*,unsigned long*,struct stacktrace_ops const*,void*) ;int /*<<< orphan*/  list; } ;

/* Variables and functions */
 TYPE_1__* curr_unwinder ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 
 TYPE_1__* select_unwinder () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct task_struct*,struct pt_regs*,unsigned long*,struct stacktrace_ops const*,void*) ; 
 scalar_t__ unwinder_faulted ; 
 int /*<<< orphan*/  unwinder_list ; 
 int /*<<< orphan*/  unwinder_lock ; 

void unwind_stack(struct task_struct *task, struct pt_regs *regs,
		  unsigned long *sp, const struct stacktrace_ops *ops,
		  void *data)
{
	unsigned long flags;

	/*
	 * The problem with unwinders with high ratings is that they are
	 * inherently more complicated than the simple ones with lower
	 * ratings. We are therefore more likely to fault in the
	 * complicated ones, e.g. hitting BUG()s. If we fault in the
	 * code for the current stack unwinder we try to downgrade to
	 * one with a lower rating.
	 *
	 * Hopefully this will give us a semi-reliable stacktrace so we
	 * can diagnose why curr_unwinder->dump() faulted.
	 */
	if (unwinder_faulted) {
		spin_lock_irqsave(&unwinder_lock, flags);

		/* Make sure no one beat us to changing the unwinder */
		if (unwinder_faulted && !list_is_singular(&unwinder_list)) {
			list_del(&curr_unwinder->list);
			curr_unwinder = select_unwinder();

			unwinder_faulted = 0;
		}

		spin_unlock_irqrestore(&unwinder_lock, flags);
	}

	curr_unwinder->dump(task, regs, sp, ops, data);
}