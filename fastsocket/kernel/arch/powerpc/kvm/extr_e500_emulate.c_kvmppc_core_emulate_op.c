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
struct kvm_vcpu {int dummy; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
#define  XOP_TLBIVAX 131 
#define  XOP_TLBRE 130 
#define  XOP_TLBSX 129 
#define  XOP_TLBWE 128 
 int get_op (unsigned int) ; 
 int get_ra (unsigned int) ; 
 int get_rb (unsigned int) ; 
 int /*<<< orphan*/  get_xop (unsigned int) ; 
 int kvmppc_booke_emulate_op (struct kvm_run*,struct kvm_vcpu*,unsigned int,int*) ; 
 int kvmppc_e500_emul_tlbivax (struct kvm_vcpu*,int,int) ; 
 int kvmppc_e500_emul_tlbre (struct kvm_vcpu*) ; 
 int kvmppc_e500_emul_tlbsx (struct kvm_vcpu*,int) ; 
 int kvmppc_e500_emul_tlbwe (struct kvm_vcpu*) ; 

int kvmppc_core_emulate_op(struct kvm_run *run, struct kvm_vcpu *vcpu,
                           unsigned int inst, int *advance)
{
	int emulated = EMULATE_DONE;
	int ra;
	int rb;

	switch (get_op(inst)) {
	case 31:
		switch (get_xop(inst)) {

		case XOP_TLBRE:
			emulated = kvmppc_e500_emul_tlbre(vcpu);
			break;

		case XOP_TLBWE:
			emulated = kvmppc_e500_emul_tlbwe(vcpu);
			break;

		case XOP_TLBSX:
			rb = get_rb(inst);
			emulated = kvmppc_e500_emul_tlbsx(vcpu,rb);
			break;

		case XOP_TLBIVAX:
			ra = get_ra(inst);
			rb = get_rb(inst);
			emulated = kvmppc_e500_emul_tlbivax(vcpu, ra, rb);
			break;

		default:
			emulated = EMULATE_FAIL;
		}

		break;

	default:
		emulated = EMULATE_FAIL;
	}

	if (emulated == EMULATE_FAIL)
		emulated = kvmppc_booke_emulate_op(run, vcpu, inst, advance);

	return emulated;
}