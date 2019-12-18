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
struct kernel_vm86_regs {int dummy; } ;

/* Variables and functions */
 int VEFLAGS ; 
 int /*<<< orphan*/  VM86_STI ; 
 int X86_EFLAGS_VIF ; 
 int X86_EFLAGS_VIP ; 
 int /*<<< orphan*/  return_to_32bit (struct kernel_vm86_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_IF(struct kernel_vm86_regs *regs)
{
	VEFLAGS |= X86_EFLAGS_VIF;
	if (VEFLAGS & X86_EFLAGS_VIP)
		return_to_32bit(regs, VM86_STI);
}