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
struct pt_regs {unsigned long bx; unsigned long dx; int orig_ax; unsigned long ip; int cs; int flags; int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; void* es; void* ds; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VM ; 
 int X86_EFLAGS_IF ; 
 int X86_EFLAGS_PF ; 
 int X86_EFLAGS_SF ; 
 int __KERNEL_CS ; 
 int /*<<< orphan*/  __KERNEL_PERCPU ; 
 int /*<<< orphan*/  __KERNEL_STACK_CANARY ; 
 void* __USER_DS ; 
 int do_fork (unsigned long,int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_kernel_rpl () ; 
 scalar_t__ kernel_thread_helper ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

int kernel_thread(int (*fn)(void *), void *arg, unsigned long flags)
{
	struct pt_regs regs;

	memset(&regs, 0, sizeof(regs));

	regs.bx = (unsigned long) fn;
	regs.dx = (unsigned long) arg;

	regs.ds = __USER_DS;
	regs.es = __USER_DS;
	regs.fs = __KERNEL_PERCPU;
	regs.gs = __KERNEL_STACK_CANARY;
	regs.orig_ax = -1;
	regs.ip = (unsigned long) kernel_thread_helper;
	regs.cs = __KERNEL_CS | get_kernel_rpl();
	regs.flags = X86_EFLAGS_IF | X86_EFLAGS_SF | X86_EFLAGS_PF | 0x2;

	/* Ok, create the new process.. */
	return do_fork(flags | CLONE_VM | CLONE_UNTRACED, 0, &regs, 0, NULL, NULL);
}