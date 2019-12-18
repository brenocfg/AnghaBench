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
struct user_regset_view {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_IA32 ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct user_regset_view const user_x86_32_view ; 
 struct user_regset_view const user_x86_64_view ; 

const struct user_regset_view *task_user_regset_view(struct task_struct *task)
{
#ifdef CONFIG_IA32_EMULATION
	if (test_tsk_thread_flag(task, TIF_IA32))
#endif
#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
		return &user_x86_32_view;
#endif
#ifdef CONFIG_X86_64
	return &user_x86_64_view;
#endif
}