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
typedef  scalar_t__ u32 ;
struct kvm_vcpu {int guest_debug; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_exit_inst_len; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;
struct TYPE_6__ {TYPE_2__ vcpu; } ;

/* Variables and functions */
#define  BP_VECTOR 137 
#define  BR_VECTOR 136 
#define  DB_VECTOR 135 
#define  DE_VECTOR 134 
#define  DF_VECTOR 133 
 scalar_t__ EMULATE_DONE ; 
#define  GP_VECTOR 132 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int KVM_GUESTDBG_USE_SW_BP ; 
#define  MF_VECTOR 131 
#define  OF_VECTOR 130 
#define  SS_VECTOR 129 
#define  UD_VECTOR 128 
 int /*<<< orphan*/  VM_EXIT_INSTRUCTION_LEN ; 
 scalar_t__ emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int) ; 
 TYPE_3__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_rmode_exception(struct kvm_vcpu *vcpu,
				  int vec, u32 err_code)
{
	/*
	 * Instruction with address size override prefix opcode 0x67
	 * Cause the #SS fault with 0 error code in VM86 mode.
	 */
	if (((vec == GP_VECTOR) || (vec == SS_VECTOR)) && err_code == 0)
		if (emulate_instruction(vcpu, 0) == EMULATE_DONE)
			return 1;
	/*
	 * Forward all other exceptions that are valid in real mode.
	 * FIXME: Breaks guest debugging in real mode, needs to be fixed with
	 *        the required debugging infrastructure rework.
	 */
	switch (vec) {
	case DB_VECTOR:
		if (vcpu->guest_debug &
		    (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP))
			return 0;
		kvm_queue_exception(vcpu, vec);
		return 1;
	case BP_VECTOR:
		/*
		 * Update instruction length as we may reinject the exception
		 * from user space while in guest debugging mode.
		 */
		to_vmx(vcpu)->vcpu.arch.event_exit_inst_len =
			vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
		if (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			return 0;
		/* fall through */
	case DE_VECTOR:
	case OF_VECTOR:
	case BR_VECTOR:
	case UD_VECTOR:
	case DF_VECTOR:
	case SS_VECTOR:
	case GP_VECTOR:
	case MF_VECTOR:
		kvm_queue_exception(vcpu, vec);
		return 1;
	}
	return 0;
}