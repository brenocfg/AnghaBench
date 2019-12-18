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
struct kvmppc_vcpu_e500 {int /*<<< orphan*/  hid1; int /*<<< orphan*/  hid0; int /*<<< orphan*/  l1csr1; int /*<<< orphan*/  mas7; int /*<<< orphan*/  mas6; int /*<<< orphan*/  mas4; int /*<<< orphan*/  mas3; int /*<<< orphan*/  mas2; int /*<<< orphan*/  mas1; int /*<<< orphan*/  mas0; int /*<<< orphan*/ * pid; } ;
struct TYPE_2__ {int /*<<< orphan*/ * gpr; int /*<<< orphan*/ * ivor; int /*<<< orphan*/  pid; int /*<<< orphan*/  shadow_pid; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 size_t BOOKE_IRQPRIO_PERFORMANCE_MONITOR ; 
 size_t BOOKE_IRQPRIO_SPE_FP_DATA ; 
 size_t BOOKE_IRQPRIO_SPE_FP_ROUND ; 
 size_t BOOKE_IRQPRIO_SPE_UNAVAIL ; 
 int EMULATE_DONE ; 
#define  SPRN_HID0 145 
#define  SPRN_HID1 144 
#define  SPRN_IVOR32 143 
#define  SPRN_IVOR33 142 
#define  SPRN_IVOR34 141 
#define  SPRN_IVOR35 140 
#define  SPRN_L1CSR1 139 
#define  SPRN_MAS0 138 
#define  SPRN_MAS1 137 
#define  SPRN_MAS2 136 
#define  SPRN_MAS3 135 
#define  SPRN_MAS4 134 
#define  SPRN_MAS6 133 
#define  SPRN_MAS7 132 
#define  SPRN_MMUCSR0 131 
#define  SPRN_PID 130 
#define  SPRN_PID1 129 
#define  SPRN_PID2 128 
 int kvmppc_booke_emulate_mtspr (struct kvm_vcpu*,int,int) ; 
 int kvmppc_e500_emul_mt_mmucsr0 (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

int kvmppc_core_emulate_mtspr(struct kvm_vcpu *vcpu, int sprn, int rs)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int emulated = EMULATE_DONE;

	switch (sprn) {
	case SPRN_PID:
		vcpu_e500->pid[0] = vcpu->arch.shadow_pid =
			vcpu->arch.pid = vcpu->arch.gpr[rs];
		break;
	case SPRN_PID1:
		vcpu_e500->pid[1] = vcpu->arch.gpr[rs]; break;
	case SPRN_PID2:
		vcpu_e500->pid[2] = vcpu->arch.gpr[rs]; break;
	case SPRN_MAS0:
		vcpu_e500->mas0 = vcpu->arch.gpr[rs]; break;
	case SPRN_MAS1:
		vcpu_e500->mas1 = vcpu->arch.gpr[rs]; break;
	case SPRN_MAS2:
		vcpu_e500->mas2 = vcpu->arch.gpr[rs]; break;
	case SPRN_MAS3:
		vcpu_e500->mas3 = vcpu->arch.gpr[rs]; break;
	case SPRN_MAS4:
		vcpu_e500->mas4 = vcpu->arch.gpr[rs]; break;
	case SPRN_MAS6:
		vcpu_e500->mas6 = vcpu->arch.gpr[rs]; break;
	case SPRN_MAS7:
		vcpu_e500->mas7 = vcpu->arch.gpr[rs]; break;
	case SPRN_L1CSR1:
		vcpu_e500->l1csr1 = vcpu->arch.gpr[rs]; break;
	case SPRN_HID0:
		vcpu_e500->hid0 = vcpu->arch.gpr[rs]; break;
	case SPRN_HID1:
		vcpu_e500->hid1 = vcpu->arch.gpr[rs]; break;

	case SPRN_MMUCSR0:
		emulated = kvmppc_e500_emul_mt_mmucsr0(vcpu_e500,
				vcpu->arch.gpr[rs]);
		break;

	/* extra exceptions */
	case SPRN_IVOR32:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR33:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR34:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR35:
		vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR] = vcpu->arch.gpr[rs];
		break;

	default:
		emulated = kvmppc_booke_emulate_mtspr(vcpu, sprn, rs);
	}

	return emulated;
}