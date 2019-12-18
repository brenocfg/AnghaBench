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
typedef  int /*<<< orphan*/  win32 ;
struct task_struct {int dummy; } ;
struct reg_window32 {int /*<<< orphan*/ * ins; int /*<<< orphan*/ * locals; } ;
struct reg_window {int /*<<< orphan*/ * ins; int /*<<< orphan*/ * locals; } ;
struct pt_regs {unsigned long* u_regs; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ STACK_BIAS ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 size_t UREG_I6 ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ get_from_target (struct task_struct*,unsigned long,struct reg_window32*,int) ; 
 scalar_t__ test_tsk_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regwindow64_get(struct task_struct *target,
			   const struct pt_regs *regs,
			   struct reg_window *wbuf)
{
	unsigned long rw_addr = regs->u_regs[UREG_I6];

	if (test_tsk_thread_flag(current, TIF_32BIT)) {
		struct reg_window32 win32;
		int i;

		if (get_from_target(target, rw_addr, &win32, sizeof(win32)))
			return -EFAULT;
		for (i = 0; i < 8; i++)
			wbuf->locals[i] = win32.locals[i];
		for (i = 0; i < 8; i++)
			wbuf->ins[i] = win32.ins[i];
	} else {
		rw_addr += STACK_BIAS;
		if (get_from_target(target, rw_addr, wbuf, sizeof(*wbuf)))
			return -EFAULT;
	}

	return 0;
}