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
 unsigned long IA32_PAGE_OFFSET ; 
 unsigned long TASK_SIZE_MAX ; 
 int /*<<< orphan*/  TIF_IA32 ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long debugreg_addr_limit(struct task_struct *task)
{
#ifdef CONFIG_IA32_EMULATION
	if (test_tsk_thread_flag(task, TIF_IA32))
		return IA32_PAGE_OFFSET - 3;
#endif
	return TASK_SIZE_MAX - 7;
}