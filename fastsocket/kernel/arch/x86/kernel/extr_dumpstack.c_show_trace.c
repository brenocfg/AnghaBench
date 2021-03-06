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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  show_trace_log_lvl (struct task_struct*,struct pt_regs*,unsigned long*,char*) ; 

void show_trace(struct task_struct *task, struct pt_regs *regs,
		unsigned long *stack)
{
	show_trace_log_lvl(task, regs, stack, "");
}