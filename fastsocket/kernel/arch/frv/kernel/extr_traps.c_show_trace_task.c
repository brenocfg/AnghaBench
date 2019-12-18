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
struct TYPE_2__ {int /*<<< orphan*/  sched_lr; int /*<<< orphan*/  lr; int /*<<< orphan*/  frame; int /*<<< orphan*/  sp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void show_trace_task(struct task_struct *tsk)
{
	printk("CONTEXT: stack=0x%lx frame=0x%p LR=0x%lx RET=0x%lx\n",
	       tsk->thread.sp, tsk->thread.frame, tsk->thread.lr, tsk->thread.sched_lr);
}