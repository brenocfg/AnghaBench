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
typedef  int /*<<< orphan*/  ufi ;
struct unw_frame_info {int dummy; } ;
struct task_struct {int dummy; } ;
struct syscall_get_set_args {unsigned int i; unsigned int n; unsigned long* args; int rw; struct pt_regs* regs; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  memset (struct unw_frame_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syscall_get_set_args_cb (struct unw_frame_info*,struct syscall_get_set_args*) ; 
 int /*<<< orphan*/  unw_init_from_blocked_task (struct unw_frame_info*,struct task_struct*) ; 
 int /*<<< orphan*/  unw_init_running (int /*<<< orphan*/  (*) (struct unw_frame_info*,struct syscall_get_set_args*),struct syscall_get_set_args*) ; 

void ia64_syscall_get_set_arguments(struct task_struct *task,
	struct pt_regs *regs, unsigned int i, unsigned int n,
	unsigned long *args, int rw)
{
	struct syscall_get_set_args data = {
		.i = i,
		.n = n,
		.args = args,
		.regs = regs,
		.rw = rw,
	};

	if (task == current)
		unw_init_running(syscall_get_set_args_cb, &data);
	else {
		struct unw_frame_info ufi;
		memset(&ufi, 0, sizeof(ufi));
		unw_init_from_blocked_task(&ufi, task);
		syscall_get_set_args_cb(&ufi, &data);
	}
}