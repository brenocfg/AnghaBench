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
 int /*<<< orphan*/  TIF_BREAKPOINT ; 
 int /*<<< orphan*/  TIF_SINGLE_STEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocd_disable (struct task_struct*) ; 

void ptrace_disable(struct task_struct *child)
{
	clear_tsk_thread_flag(child, TIF_SINGLE_STEP);
	clear_tsk_thread_flag(child, TIF_BREAKPOINT);
	ocd_disable(child);
}