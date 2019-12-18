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
struct TYPE_2__ {int /*<<< orphan*/  ccr1; int /*<<< orphan*/ * gpr; int /*<<< orphan*/  ccr0; int /*<<< orphan*/  mmucr; int /*<<< orphan*/  pid; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMULATED_MFSPR_EXITS ; 
 int EMULATE_DONE ; 
#define  SPRN_CCR0 131 
#define  SPRN_CCR1 130 
#define  SPRN_MMUCR 129 
#define  SPRN_PID 128 
 int kvmppc_booke_emulate_mfspr (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  kvmppc_set_exit_type (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

int kvmppc_core_emulate_mfspr(struct kvm_vcpu *vcpu, int sprn, int rt)
{
	int emulated = EMULATE_DONE;

	switch (sprn) {
	case SPRN_PID:
		vcpu->arch.gpr[rt] = vcpu->arch.pid; break;
	case SPRN_MMUCR:
		vcpu->arch.gpr[rt] = vcpu->arch.mmucr; break;
	case SPRN_CCR0:
		vcpu->arch.gpr[rt] = vcpu->arch.ccr0; break;
	case SPRN_CCR1:
		vcpu->arch.gpr[rt] = vcpu->arch.ccr1; break;
	default:
		emulated = kvmppc_booke_emulate_mfspr(vcpu, sprn, rt);
	}

	kvmppc_set_exit_type(vcpu, EMULATED_MFSPR_EXITS);
	return emulated;
}