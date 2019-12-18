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
struct pt_regs {int ax; } ;
struct kernel_vm86_regs {int dummy; } ;

/* Variables and functions */
 struct pt_regs* save_v86_state (struct kernel_vm86_regs*) ; 

__attribute__((used)) static inline void return_to_32bit(struct kernel_vm86_regs *regs16, int retval)
{
	struct pt_regs *regs32;

	regs32 = save_v86_state(regs16);
	regs32->ax = retval;
	__asm__ __volatile__("movl %0,%%esp\n\t"
		"movl %1,%%ebp\n\t"
		"jmp resume_userspace"
		: : "r" (regs32), "r" (current_thread_info()));
}