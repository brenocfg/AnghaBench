#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {int nmi_injected; void* event_exit_inst_len; } ;
struct TYPE_10__ {TYPE_1__ arch; } ;
struct vcpu_vmx {int idt_vectoring_info; scalar_t__ exit_reason; TYPE_2__ vcpu; int /*<<< orphan*/  entry_time; int /*<<< orphan*/  vnmi_blocked_time; int /*<<< orphan*/  soft_vnmi_blocked; } ;

/* Variables and functions */
 int DF_VECTOR ; 
 scalar_t__ EXIT_REASON_EXCEPTION_NMI ; 
 scalar_t__ EXIT_REASON_MCE_DURING_VMENTRY ; 
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int /*<<< orphan*/  GUEST_INTR_STATE_NMI ; 
 int /*<<< orphan*/  IDT_VECTORING_ERROR_CODE ; 
 int INTR_INFO_INTR_TYPE_MASK ; 
 int INTR_INFO_UNBLOCK_NMI ; 
 int INTR_INFO_VALID_MASK ; 
 int INTR_INFO_VECTOR_MASK ; 
#define  INTR_TYPE_EXT_INTR 132 
#define  INTR_TYPE_HARD_EXCEPTION 131 
#define  INTR_TYPE_NMI_INTR 130 
#define  INTR_TYPE_SOFT_EXCEPTION 129 
#define  INTR_TYPE_SOFT_INTR 128 
 int VECTORING_INFO_DELIVER_CODE_MASK ; 
 int VECTORING_INFO_TYPE_MASK ; 
 int VECTORING_INFO_VALID_MASK ; 
 int VECTORING_INFO_VECTOR_MASK ; 
 int /*<<< orphan*/  VM_EXIT_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  VM_EXIT_INTR_INFO ; 
 int /*<<< orphan*/  VM_EXIT_REASON ; 
 scalar_t__ cpu_has_virtual_nmis () ; 
 scalar_t__ is_machine_check (int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_after_handle_nmi (TYPE_2__*) ; 
 int /*<<< orphan*/  kvm_before_handle_nmi (TYPE_2__*) ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  kvm_clear_interrupt_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  kvm_machine_check () ; 
 int /*<<< orphan*/  kvm_queue_exception (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kvm_queue_exception_e (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  kvm_queue_interrupt (TYPE_2__*,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_clear_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_complete_interrupts(struct vcpu_vmx *vmx)
{
	u32 exit_intr_info;
	u32 idt_vectoring_info = vmx->idt_vectoring_info;
	bool unblock_nmi;
	u8 vector;
	int type;
	bool idtv_info_valid;

	exit_intr_info = vmcs_read32(VM_EXIT_INTR_INFO);

	vmx->exit_reason = vmcs_read32(VM_EXIT_REASON);

	/* Handle machine checks before interrupts are enabled */
	if ((vmx->exit_reason == EXIT_REASON_MCE_DURING_VMENTRY)
	    || (vmx->exit_reason == EXIT_REASON_EXCEPTION_NMI
		&& is_machine_check(exit_intr_info)))
		kvm_machine_check();

	/* We need to handle NMIs before interrupts are enabled */
	if ((exit_intr_info & INTR_INFO_INTR_TYPE_MASK) == INTR_TYPE_NMI_INTR &&
	    (exit_intr_info & INTR_INFO_VALID_MASK)) {
		kvm_before_handle_nmi(&vmx->vcpu);
		asm("int $2");
		kvm_after_handle_nmi(&vmx->vcpu);
	}

	idtv_info_valid = idt_vectoring_info & VECTORING_INFO_VALID_MASK;

	if (cpu_has_virtual_nmis()) {
		unblock_nmi = (exit_intr_info & INTR_INFO_UNBLOCK_NMI) != 0;
		vector = exit_intr_info & INTR_INFO_VECTOR_MASK;
		/*
		 * SDM 3: 27.7.1.2 (September 2008)
		 * Re-set bit "block by NMI" before VM entry if vmexit caused by
		 * a guest IRET fault.
		 * SDM 3: 23.2.2 (September 2008)
		 * Bit 12 is undefined in any of the following cases:
		 *  If the VM exit sets the valid bit in the IDT-vectoring
		 *   information field.
		 *  If the VM exit is due to a double fault.
		 */
		if ((exit_intr_info & INTR_INFO_VALID_MASK) && unblock_nmi &&
		    vector != DF_VECTOR && !idtv_info_valid)
			vmcs_set_bits(GUEST_INTERRUPTIBILITY_INFO,
				      GUEST_INTR_STATE_NMI);
	} else if (unlikely(vmx->soft_vnmi_blocked))
		vmx->vnmi_blocked_time +=
			ktime_to_ns(ktime_sub(ktime_get(), vmx->entry_time));

	vmx->vcpu.arch.nmi_injected = false;
	kvm_clear_exception_queue(&vmx->vcpu);
	kvm_clear_interrupt_queue(&vmx->vcpu);

	if (!idtv_info_valid)
		return;

	vector = idt_vectoring_info & VECTORING_INFO_VECTOR_MASK;
	type = idt_vectoring_info & VECTORING_INFO_TYPE_MASK;

	switch (type) {
	case INTR_TYPE_NMI_INTR:
		vmx->vcpu.arch.nmi_injected = true;
		/*
		 * SDM 3: 27.7.1.2 (September 2008)
		 * Clear bit "block by NMI" before VM entry if a NMI
		 * delivery faulted.
		 */
		vmcs_clear_bits(GUEST_INTERRUPTIBILITY_INFO,
				GUEST_INTR_STATE_NMI);
		break;
	case INTR_TYPE_SOFT_EXCEPTION:
		vmx->vcpu.arch.event_exit_inst_len =
			vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
		/* fall through */
	case INTR_TYPE_HARD_EXCEPTION:
		if (idt_vectoring_info & VECTORING_INFO_DELIVER_CODE_MASK) {
			u32 err = vmcs_read32(IDT_VECTORING_ERROR_CODE);
			kvm_queue_exception_e(&vmx->vcpu, vector, err);
		} else
			kvm_queue_exception(&vmx->vcpu, vector);
		break;
	case INTR_TYPE_SOFT_INTR:
		vmx->vcpu.arch.event_exit_inst_len =
			vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
		/* fall through */
	case INTR_TYPE_EXT_INTR:
		kvm_queue_interrupt(&vmx->vcpu, vector,
			type == INTR_TYPE_SOFT_INTR);
		break;
	default:
		break;
	}
}