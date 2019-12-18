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
struct task_struct {int ptrace; } ;

/* Variables and functions */
 int PT_SINGLESTEP ; 
 int /*<<< orphan*/  ptrace_cancel_bpt (struct task_struct*) ; 

__attribute__((used)) static inline void single_step_clear(struct task_struct *task)
{
	if (task->ptrace & PT_SINGLESTEP)
		ptrace_cancel_bpt(task);
}