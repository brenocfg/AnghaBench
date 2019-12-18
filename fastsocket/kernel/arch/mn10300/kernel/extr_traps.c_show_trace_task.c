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
struct TYPE_2__ {unsigned long sp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  show_trace (unsigned long*) ; 

void show_trace_task(struct task_struct *tsk)
{
	unsigned long sp = tsk->thread.sp;

	/* User space on another CPU? */
	if ((sp ^ (unsigned long) tsk) & (PAGE_MASK << 1))
		return;

	show_trace((unsigned long *) sp);
}