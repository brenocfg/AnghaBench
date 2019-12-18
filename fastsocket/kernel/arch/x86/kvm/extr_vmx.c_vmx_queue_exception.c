#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int event_exit_inst_len; } ;
struct TYPE_8__ {TYPE_3__ arch; } ;
struct TYPE_5__ {int pending; unsigned int vector; scalar_t__ rip; } ;
struct TYPE_6__ {TYPE_1__ irq; scalar_t__ vm86_active; } ;
struct vcpu_vmx {TYPE_4__ vcpu; TYPE_2__ rmode; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int INTR_INFO_DELIVER_CODE_MASK ; 
 unsigned int INTR_INFO_VALID_MASK ; 
 int INTR_TYPE_HARD_EXCEPTION ; 
 int INTR_TYPE_SOFT_EXCEPTION ; 
 int INTR_TYPE_SOFT_INTR ; 
 int /*<<< orphan*/  VM_ENTRY_EXCEPTION_ERROR_CODE ; 
 int /*<<< orphan*/  VM_ENTRY_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  VM_ENTRY_INTR_INFO_FIELD ; 
 scalar_t__ kvm_exception_is_soft (unsigned int) ; 
 scalar_t__ kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,scalar_t__) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmx_clear_hlt (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_queue_exception(struct kvm_vcpu *vcpu, unsigned nr,
				bool has_error_code, u32 error_code)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u32 intr_info = nr | INTR_INFO_VALID_MASK;

	if (has_error_code) {
		vmcs_write32(VM_ENTRY_EXCEPTION_ERROR_CODE, error_code);
		intr_info |= INTR_INFO_DELIVER_CODE_MASK;
	}

	if (vmx->rmode.vm86_active) {
		vmx->rmode.irq.pending = true;
		vmx->rmode.irq.vector = nr;
		vmx->rmode.irq.rip = kvm_rip_read(vcpu);
		if (kvm_exception_is_soft(nr))
			vmx->rmode.irq.rip +=
				vmx->vcpu.arch.event_exit_inst_len;
		intr_info |= INTR_TYPE_SOFT_INTR;
		vmcs_write32(VM_ENTRY_INTR_INFO_FIELD, intr_info);
		vmcs_write32(VM_ENTRY_INSTRUCTION_LEN, 1);
		kvm_rip_write(vcpu, vmx->rmode.irq.rip - 1);
		return;
	}

	if (kvm_exception_is_soft(nr)) {
		vmcs_write32(VM_ENTRY_INSTRUCTION_LEN,
			     vmx->vcpu.arch.event_exit_inst_len);
		intr_info |= INTR_TYPE_SOFT_EXCEPTION;
	} else
		intr_info |= INTR_TYPE_HARD_EXCEPTION;

	vmcs_write32(VM_ENTRY_INTR_INFO_FIELD, intr_info);
	vmx_clear_hlt(vcpu);
}