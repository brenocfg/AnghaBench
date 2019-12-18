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

/* Variables and functions */
 int /*<<< orphan*/  show_stack_log_lvl (struct task_struct*,unsigned long,int /*<<< orphan*/ *,char*) ; 

void show_stack(struct task_struct *tsk, unsigned long *stack)
{
	show_stack_log_lvl(tsk, (unsigned long)stack, NULL, "");
}