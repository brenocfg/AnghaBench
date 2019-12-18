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
struct pt_regs {unsigned long sp; } ;

/* Variables and functions */
 unsigned long FRAME_SIZE_FULL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  show_regs_log_lvl (struct pt_regs*,char*) ; 
 int /*<<< orphan*/  show_trace_log_lvl (int /*<<< orphan*/ ,unsigned long*,struct pt_regs*,char*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void show_regs(struct pt_regs *regs)
{
	unsigned long sp = regs->sp;

	if (!user_mode(regs))
		sp = (unsigned long)regs + FRAME_SIZE_FULL;

	show_regs_log_lvl(regs, "");
	show_trace_log_lvl(current, (unsigned long *)sp, regs, "");
}