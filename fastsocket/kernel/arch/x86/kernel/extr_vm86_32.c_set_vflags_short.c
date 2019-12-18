#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct kernel_vm86_regs {TYPE_2__ pt; } ;
struct TYPE_4__ {int /*<<< orphan*/  v86mask; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_MASK ; 
 int /*<<< orphan*/  VFLAGS ; 
 unsigned short X86_EFLAGS_IF ; 
 int /*<<< orphan*/  clear_IF (struct kernel_vm86_regs*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  set_IF (struct kernel_vm86_regs*) ; 
 int /*<<< orphan*/  set_flags (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_vflags_short(unsigned short flags, struct kernel_vm86_regs *regs)
{
	set_flags(VFLAGS, flags, current->thread.v86mask);
	set_flags(regs->pt.flags, flags, SAFE_MASK);
	if (flags & X86_EFLAGS_IF)
		set_IF(regs);
	else
		clear_IF(regs);
}