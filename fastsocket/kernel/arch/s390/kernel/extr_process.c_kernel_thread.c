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
struct TYPE_2__ {int mask; unsigned long addr; } ;
struct pt_regs {unsigned long* gprs; int orig_gpr2; TYPE_1__ psw; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VM ; 
 unsigned long PSW_ADDR_AMODE ; 
 int PSW_MASK_EXT ; 
 int PSW_MASK_IO ; 
 scalar_t__ do_exit ; 
 int do_fork (unsigned long,int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kernel_thread_starter ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 int psw_kernel_bits ; 

int kernel_thread(int (*fn)(void *), void * arg, unsigned long flags)
{
	struct pt_regs regs;

	memset(&regs, 0, sizeof(regs));
	regs.psw.mask = psw_kernel_bits | PSW_MASK_IO | PSW_MASK_EXT;
	regs.psw.addr = (unsigned long) kernel_thread_starter | PSW_ADDR_AMODE;
	regs.gprs[9] = (unsigned long) fn;
	regs.gprs[10] = (unsigned long) arg;
	regs.gprs[11] = (unsigned long) do_exit;
	regs.orig_gpr2 = -1;

	/* Ok, create the new process.. */
	return do_fork(flags | CLONE_VM | CLONE_UNTRACED,
		       0, &regs, 0, NULL, NULL);
}