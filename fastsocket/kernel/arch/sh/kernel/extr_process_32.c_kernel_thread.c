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
struct pt_regs {unsigned long* regs; unsigned long pc; int sr; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VM ; 
 int do_fork (unsigned long,int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kernel_thread_helper ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

int kernel_thread(int (*fn)(void *), void * arg, unsigned long flags)
{
	struct pt_regs regs;
	int pid;

	memset(&regs, 0, sizeof(regs));
	regs.regs[4] = (unsigned long)arg;
	regs.regs[5] = (unsigned long)fn;

	regs.pc = (unsigned long)kernel_thread_helper;
	regs.sr = (1 << 30);

	/* Ok, create the new process.. */
	pid = do_fork(flags | CLONE_VM | CLONE_UNTRACED, 0,
		      &regs, 0, NULL, NULL);

	return pid;
}