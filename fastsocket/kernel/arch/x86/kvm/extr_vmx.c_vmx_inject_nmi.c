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
struct TYPE_5__ {int pending; int vector; scalar_t__ rip; } ;
struct TYPE_6__ {TYPE_2__ irq; scalar_t__ vm86_active; } ;
struct vcpu_vmx {int soft_vnmi_blocked; TYPE_3__ rmode; scalar_t__ vnmi_blocked_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  nmi_injections; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;

/* Variables and functions */
 int INTR_INFO_VALID_MASK ; 
 int INTR_TYPE_NMI_INTR ; 
 int INTR_TYPE_SOFT_INTR ; 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  VM_ENTRY_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  VM_ENTRY_INTR_INFO_FIELD ; 
 int /*<<< orphan*/  cpu_has_virtual_nmis () ; 
 scalar_t__ kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,scalar_t__) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmx_clear_hlt (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_inject_nmi(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (!cpu_has_virtual_nmis()) {
		/*
		 * Tracking the NMI-blocked state in software is built upon
		 * finding the next open IRQ window. This, in turn, depends on
		 * well-behaving guests: They have to keep IRQs disabled at
		 * least as long as the NMI handler runs. Otherwise we may
		 * cause NMI nesting, maybe breaking the guest. But as this is
		 * highly unlikely, we can live with the residual risk.
		 */
		vmx->soft_vnmi_blocked = 1;
		vmx->vnmi_blocked_time = 0;
	}

	++vcpu->stat.nmi_injections;
	if (vmx->rmode.vm86_active) {
		vmx->rmode.irq.pending = true;
		vmx->rmode.irq.vector = NMI_VECTOR;
		vmx->rmode.irq.rip = kvm_rip_read(vcpu);
		vmcs_write32(VM_ENTRY_INTR_INFO_FIELD,
			     NMI_VECTOR | INTR_TYPE_SOFT_INTR |
			     INTR_INFO_VALID_MASK);
		vmcs_write32(VM_ENTRY_INSTRUCTION_LEN, 1);
		kvm_rip_write(vcpu, vmx->rmode.irq.rip - 1);
		return;
	}
	vmcs_write32(VM_ENTRY_INTR_INFO_FIELD,
			INTR_TYPE_NMI_INTR | INTR_INFO_VALID_MASK | NMI_VECTOR);
	vmx_clear_hlt(vcpu);
}