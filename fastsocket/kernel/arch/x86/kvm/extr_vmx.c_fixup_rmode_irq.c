#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ rip; int vector; scalar_t__ pending; } ;
struct TYPE_4__ {TYPE_1__ irq; } ;
struct vcpu_vmx {int idt_vectoring_info; TYPE_2__ rmode; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int INTR_TYPE_EXT_INTR ; 
 int VECTORING_INFO_TYPE_MASK ; 
 int VECTORING_INFO_VALID_MASK ; 
 scalar_t__ kvm_rip_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_rip_write (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void fixup_rmode_irq(struct vcpu_vmx *vmx)
{
	vmx->rmode.irq.pending = 0;
	if (kvm_rip_read(&vmx->vcpu) + 1 != vmx->rmode.irq.rip)
		return;
	kvm_rip_write(&vmx->vcpu, vmx->rmode.irq.rip);
	if (vmx->idt_vectoring_info & VECTORING_INFO_VALID_MASK) {
		vmx->idt_vectoring_info &= ~VECTORING_INFO_TYPE_MASK;
		vmx->idt_vectoring_info |= INTR_TYPE_EXT_INTR;
		return;
	}
	vmx->idt_vectoring_info =
		VECTORING_INFO_VALID_MASK
		| INTR_TYPE_EXT_INTR
		| vmx->rmode.irq.vector;
}