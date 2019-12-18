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
typedef  int u32 ;
struct x86_emulate_ctxt {int interruptibility; int /*<<< orphan*/  vcpu; } ;
struct TYPE_2__ {int (* get_interrupt_shadow ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void toggle_interruptibility(struct x86_emulate_ctxt *ctxt, u32 mask)
{
	u32 int_shadow = kvm_x86_ops->get_interrupt_shadow(ctxt->vcpu, mask);
	/*
	 * an sti; sti; sequence only disable interrupts for the first
	 * instruction. So, if the last instruction, be it emulated or
	 * not, left the system with the INT_STI flag enabled, it
	 * means that the last instruction is an sti. We should not
	 * leave the flag on in this case. The same goes for mov ss
	 */
	if (!(int_shadow & mask))
		ctxt->interruptibility = mask;
}