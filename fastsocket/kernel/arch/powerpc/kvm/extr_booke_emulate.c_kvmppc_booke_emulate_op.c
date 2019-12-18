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
struct TYPE_2__ {unsigned int* gpr; unsigned int msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMULATED_MFMSR_EXITS ; 
 int /*<<< orphan*/  EMULATED_MTMSR_EXITS ; 
 int /*<<< orphan*/  EMULATED_RFI_EXITS ; 
 int /*<<< orphan*/  EMULATED_WRTEE_EXITS ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 unsigned int MSR_EE ; 
#define  OP_19_XOP_RFI 132 
#define  OP_31_XOP_MFMSR 131 
#define  OP_31_XOP_MTMSR 130 
#define  OP_31_XOP_WRTEE 129 
#define  OP_31_XOP_WRTEEI 128 
 int get_op (unsigned int) ; 
 int get_rs (unsigned int) ; 
 int get_rt (unsigned int) ; 
 int /*<<< orphan*/  get_xop (unsigned int) ; 
 int /*<<< orphan*/  kvmppc_emul_rfi (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_exit_type (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,unsigned int) ; 

int kvmppc_booke_emulate_op(struct kvm_run *run, struct kvm_vcpu *vcpu,
                            unsigned int inst, int *advance)
{
	int emulated = EMULATE_DONE;
	int rs;
	int rt;

	switch (get_op(inst)) {
	case 19:
		switch (get_xop(inst)) {
		case OP_19_XOP_RFI:
			kvmppc_emul_rfi(vcpu);
			kvmppc_set_exit_type(vcpu, EMULATED_RFI_EXITS);
			*advance = 0;
			break;

		default:
			emulated = EMULATE_FAIL;
			break;
		}
		break;

	case 31:
		switch (get_xop(inst)) {

		case OP_31_XOP_MFMSR:
			rt = get_rt(inst);
			vcpu->arch.gpr[rt] = vcpu->arch.msr;
			kvmppc_set_exit_type(vcpu, EMULATED_MFMSR_EXITS);
			break;

		case OP_31_XOP_MTMSR:
			rs = get_rs(inst);
			kvmppc_set_exit_type(vcpu, EMULATED_MTMSR_EXITS);
			kvmppc_set_msr(vcpu, vcpu->arch.gpr[rs]);
			break;

		case OP_31_XOP_WRTEE:
			rs = get_rs(inst);
			vcpu->arch.msr = (vcpu->arch.msr & ~MSR_EE)
							 | (vcpu->arch.gpr[rs] & MSR_EE);
			kvmppc_set_exit_type(vcpu, EMULATED_WRTEE_EXITS);
			break;

		case OP_31_XOP_WRTEEI:
			vcpu->arch.msr = (vcpu->arch.msr & ~MSR_EE)
							 | (inst & MSR_EE);
			kvmppc_set_exit_type(vcpu, EMULATED_WRTEE_EXITS);
			break;

		default:
			emulated = EMULATE_FAIL;
		}

		break;

	default:
		emulated = EMULATE_FAIL;
	}

	return emulated;
}