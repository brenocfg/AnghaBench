#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {void* event_exit_inst_len; } ;
struct TYPE_13__ {TYPE_4__ arch; } ;
struct TYPE_10__ {scalar_t__ vm86_active; } ;
struct vcpu_vmx {int idt_vectoring_info; TYPE_5__ vcpu; TYPE_2__ rmode; } ;
struct TYPE_11__ {unsigned long dr6; scalar_t__ halt_request; } ;
struct kvm_vcpu {int guest_debug; TYPE_3__ arch; struct kvm_run* run; } ;
struct TYPE_16__ {int exception; int error_code; } ;
struct TYPE_14__ {unsigned long dr6; unsigned long dr7; unsigned long pc; int exception; } ;
struct TYPE_15__ {TYPE_6__ arch; } ;
struct TYPE_9__ {int ndata; int* data; int /*<<< orphan*/  suberror; } ;
struct kvm_run {TYPE_8__ ex; int /*<<< orphan*/  exit_reason; TYPE_7__ debug; TYPE_1__ internal; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
#define  BP_VECTOR 129 
 int /*<<< orphan*/  BUG () ; 
#define  DB_VECTOR 128 
 unsigned long DR6_FIXED_1 ; 
 int EMULATE_DONE ; 
 int /*<<< orphan*/  EMULTYPE_TRAP_UD ; 
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 int /*<<< orphan*/  GUEST_CS_BASE ; 
 int /*<<< orphan*/  GUEST_DR7 ; 
 int INTR_INFO_DELIVER_CODE_MASK ; 
 int INTR_INFO_INTR_TYPE_MASK ; 
 int INTR_INFO_VECTOR_MASK ; 
 int INTR_TYPE_NMI_INTR ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int /*<<< orphan*/  KVM_EXIT_EXCEPTION ; 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int /*<<< orphan*/  KVM_INTERNAL_ERROR_SIMUL_EX ; 
 int const UD_VECTOR ; 
 int VECTORING_INFO_VALID_MASK ; 
 int /*<<< orphan*/  VM_EXIT_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  VM_EXIT_INTR_ERROR_CODE ; 
 int /*<<< orphan*/  VM_EXIT_INTR_INFO ; 
 int emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_ept ; 
 int handle_machine_check (struct kvm_vcpu*) ; 
 scalar_t__ handle_rmode_exception (struct kvm_vcpu*,int,int) ; 
 scalar_t__ is_invalid_opcode (int) ; 
 scalar_t__ is_machine_check (int) ; 
 scalar_t__ is_no_device (int) ; 
 scalar_t__ is_page_fault (int) ; 
 int kvm_emulate_halt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_event_needs_reinjection (struct kvm_vcpu*) ; 
 int kvm_mmu_page_fault (struct kvm_vcpu*,unsigned long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_unprotect_page_virt (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int const) ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_page_fault (unsigned long,int) ; 
 void* vmcs_read32 (int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_fpu_activate (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_exception(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct kvm_run *kvm_run = vcpu->run;
	u32 intr_info, ex_no, error_code;
	unsigned long cr2, rip, dr6;
	u32 vect_info;
	enum emulation_result er;

	vect_info = vmx->idt_vectoring_info;
	intr_info = vmcs_read32(VM_EXIT_INTR_INFO);

	if (is_machine_check(intr_info))
		return handle_machine_check(vcpu);

	if ((vect_info & VECTORING_INFO_VALID_MASK) &&
	    !is_page_fault(intr_info)) {
		vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->internal.suberror = KVM_INTERNAL_ERROR_SIMUL_EX;
		vcpu->run->internal.ndata = 2;
		vcpu->run->internal.data[0] = vect_info;
		vcpu->run->internal.data[1] = intr_info;
		return 0;
	}

	if ((intr_info & INTR_INFO_INTR_TYPE_MASK) == INTR_TYPE_NMI_INTR)
		return 1;  /* already handled by vmx_vcpu_run() */

	if (is_no_device(intr_info)) {
		vmx_fpu_activate(vcpu);
		return 1;
	}

	if (is_invalid_opcode(intr_info)) {
		er = emulate_instruction(vcpu, EMULTYPE_TRAP_UD);
		if (er != EMULATE_DONE)
			kvm_queue_exception(vcpu, UD_VECTOR);
		return 1;
	}

	error_code = 0;
	rip = kvm_rip_read(vcpu);
	if (intr_info & INTR_INFO_DELIVER_CODE_MASK)
		error_code = vmcs_read32(VM_EXIT_INTR_ERROR_CODE);
	if (is_page_fault(intr_info)) {
		/* EPT won't cause page fault directly */
		if (enable_ept)
			BUG();
		cr2 = vmcs_readl(EXIT_QUALIFICATION);
		trace_kvm_page_fault(cr2, error_code);

		if (kvm_event_needs_reinjection(vcpu))
			kvm_mmu_unprotect_page_virt(vcpu, cr2);
		return kvm_mmu_page_fault(vcpu, cr2, error_code, NULL, 0);
	}

	if (vmx->rmode.vm86_active &&
	    handle_rmode_exception(vcpu, intr_info & INTR_INFO_VECTOR_MASK,
								error_code)) {
		if (vcpu->arch.halt_request) {
			vcpu->arch.halt_request = 0;
			return kvm_emulate_halt(vcpu);
		}
		return 1;
	}

	ex_no = intr_info & INTR_INFO_VECTOR_MASK;
	switch (ex_no) {
	case DB_VECTOR:
		dr6 = vmcs_readl(EXIT_QUALIFICATION);
		if (!(vcpu->guest_debug &
		      (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP))) {
			vcpu->arch.dr6 = dr6 | DR6_FIXED_1;
			kvm_queue_exception(vcpu, DB_VECTOR);
			return 1;
		}
		kvm_run->debug.arch.dr6 = dr6 | DR6_FIXED_1;
		kvm_run->debug.arch.dr7 = vmcs_readl(GUEST_DR7);
		/* fall through */
	case BP_VECTOR:
		/*
		 * Update instruction length as we may reinject #BP from
		 * user space while in guest debugging mode. Reading it for
		 * #DB as well causes no harm, it is not used in that case.
		 */
		vmx->vcpu.arch.event_exit_inst_len =
			vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
		kvm_run->exit_reason = KVM_EXIT_DEBUG;
		kvm_run->debug.arch.pc = vmcs_readl(GUEST_CS_BASE) + rip;
		kvm_run->debug.arch.exception = ex_no;
		break;
	default:
		kvm_run->exit_reason = KVM_EXIT_EXCEPTION;
		kvm_run->ex.exception = ex_no;
		kvm_run->ex.error_code = error_code;
		break;
	}
	return 0;
}