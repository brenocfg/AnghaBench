#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  epsw; } ;
struct user {TYPE_1__ regs; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 long EPSW_T ; 
 long get_stack_long (struct task_struct*,unsigned long) ; 
 int /*<<< orphan*/  put_stack_long (struct task_struct*,unsigned long,long) ; 

void user_disable_single_step(struct task_struct *child)
{
#ifndef CONFIG_MN10300_USING_JTAG
	struct user *dummy = NULL;
	long tmp;

	tmp = get_stack_long(child, (unsigned long) &dummy->regs.epsw);
	tmp &= ~EPSW_T;
	put_stack_long(child, (unsigned long) &dummy->regs.epsw, tmp);
#endif
}