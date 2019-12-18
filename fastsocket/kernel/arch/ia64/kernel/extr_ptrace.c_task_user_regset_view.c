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
 scalar_t__ IS_IA32_PROCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 
 struct user_regset_view const user_ia64_view ; 

const struct user_regset_view *task_user_regset_view(struct task_struct *tsk)
{
#ifdef CONFIG_IA32_SUPPORT
	extern const struct user_regset_view user_ia32_view;
	if (IS_IA32_PROCESS(task_pt_regs(tsk)))
		return &user_ia32_view;
#endif
	return &user_ia64_view;
}