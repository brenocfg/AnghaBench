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
struct TYPE_2__ {int /*<<< orphan*/ * gpr; int /*<<< orphan*/  ccr1; int /*<<< orphan*/  ccr0; int /*<<< orphan*/  mmucr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMULATED_MTSPR_EXITS ; 
 int EMULATE_DONE ; 
#define  SPRN_CCR0 131 
#define  SPRN_CCR1 130 
#define  SPRN_MMUCR 129 
#define  SPRN_PID 128 
 int kvmppc_booke_emulate_mtspr (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  kvmppc_set_exit_type (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_pid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

int kvmppc_core_emulate_mtspr(struct kvm_vcpu *vcpu, int sprn, int rs)
{
	int emulated = EMULATE_DONE;

	switch (sprn) {
	case SPRN_PID:
		kvmppc_set_pid(vcpu, vcpu->arch.gpr[rs]); break;
	case SPRN_MMUCR:
		vcpu->arch.mmucr = vcpu->arch.gpr[rs]; break;
	case SPRN_CCR0:
		vcpu->arch.ccr0 = vcpu->arch.gpr[rs]; break;
	case SPRN_CCR1:
		vcpu->arch.ccr1 = vcpu->arch.gpr[rs]; break;
	default:
		emulated = kvmppc_booke_emulate_mtspr(vcpu, sprn, rs);
	}

	kvmppc_set_exit_type(vcpu, EMULATED_MTSPR_EXITS);
	return emulated;
}