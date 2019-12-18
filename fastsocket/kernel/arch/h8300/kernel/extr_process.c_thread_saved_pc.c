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
struct TYPE_2__ {scalar_t__ esp0; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {unsigned long pc; } ;

/* Variables and functions */

unsigned long thread_saved_pc(struct task_struct *tsk)
{
	return ((struct pt_regs *)tsk->thread.esp0)->pc;
}