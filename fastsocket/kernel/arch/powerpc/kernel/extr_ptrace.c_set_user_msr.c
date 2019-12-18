#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* regs; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_3__ {unsigned long msr; } ;

/* Variables and functions */
 unsigned long MSR_DEBUGCHANGE ; 

__attribute__((used)) static int set_user_msr(struct task_struct *task, unsigned long msr)
{
	task->thread.regs->msr &= ~MSR_DEBUGCHANGE;
	task->thread.regs->msr |= msr & MSR_DEBUGCHANGE;
	return 0;
}