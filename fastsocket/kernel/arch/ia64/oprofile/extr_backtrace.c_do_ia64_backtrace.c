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
typedef  scalar_t__ u_long ;
struct unw_frame_info {int dummy; } ;
struct switch_stack {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  depth; scalar_t__ regs; } ;
typedef  TYPE_1__ ia64_backtrace_t ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 scalar_t__ next_frame (TYPE_1__*) ; 
 int /*<<< orphan*/  oprofile_add_trace (scalar_t__) ; 
 int /*<<< orphan*/  unw_get_ip (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  unw_get_sp (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  unw_init_frame_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct switch_stack*) ; 
 scalar_t__ unw_is_intr_frame (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_ia64_backtrace(struct unw_frame_info *info, void *vdata)
{
	ia64_backtrace_t *bt = vdata;
	struct switch_stack *sw;
	int count = 0;
	u_long pc, sp;

	sw = (struct switch_stack *)(info+1);
	/* padding from unw_init_running */
	sw = (struct switch_stack *)(((unsigned long)sw + 15) & ~15);

	unw_init_frame_info(&bt->frame, current, sw);

	/* skip over interrupt frame and oprofile calls */
	do {
		unw_get_sp(&bt->frame, &sp);
		if (sp >= (u_long)bt->regs)
			break;
		if (!next_frame(bt))
			return;
	} while (count++ < 200);

	/* finally, grab the actual sample */
	while (bt->depth-- && next_frame(bt)) {
		unw_get_ip(&bt->frame, &pc);
		oprofile_add_trace(pc);
		if (unw_is_intr_frame(&bt->frame)) {
			/*
			 * Interrupt received on kernel stack; this can
			 * happen when timer interrupt fires while processing
			 * a softirq from the tail end of a hardware interrupt
			 * which interrupted a system call.  Don't laugh, it
			 * happens!  Splice the backtrace into two parts to
			 * avoid spurious cycles in the gprof output.
			 */
			/* TODO: split rather than drop the 2nd half */
			break;
		}
	}
}