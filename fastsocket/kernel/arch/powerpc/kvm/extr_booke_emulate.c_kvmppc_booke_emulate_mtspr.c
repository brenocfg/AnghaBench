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
struct TYPE_2__ {int /*<<< orphan*/ * gpr; int /*<<< orphan*/ * ivor; int /*<<< orphan*/  ivpr; int /*<<< orphan*/  sprg7; int /*<<< orphan*/  sprg6; int /*<<< orphan*/  sprg5; int /*<<< orphan*/  sprg4; int /*<<< orphan*/  tcr; int /*<<< orphan*/  tsr; int /*<<< orphan*/  dbsr; int /*<<< orphan*/  dbcr1; int /*<<< orphan*/  dbcr0; int /*<<< orphan*/  esr; int /*<<< orphan*/  dear; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 size_t BOOKE_IRQPRIO_ALIGNMENT ; 
 size_t BOOKE_IRQPRIO_AP_UNAVAIL ; 
 size_t BOOKE_IRQPRIO_CRITICAL ; 
 size_t BOOKE_IRQPRIO_DATA_STORAGE ; 
 size_t BOOKE_IRQPRIO_DEBUG ; 
 size_t BOOKE_IRQPRIO_DECREMENTER ; 
 size_t BOOKE_IRQPRIO_DTLB_MISS ; 
 size_t BOOKE_IRQPRIO_EXTERNAL ; 
 size_t BOOKE_IRQPRIO_FIT ; 
 size_t BOOKE_IRQPRIO_FP_UNAVAIL ; 
 size_t BOOKE_IRQPRIO_INST_STORAGE ; 
 size_t BOOKE_IRQPRIO_ITLB_MISS ; 
 size_t BOOKE_IRQPRIO_MACHINE_CHECK ; 
 size_t BOOKE_IRQPRIO_PROGRAM ; 
 size_t BOOKE_IRQPRIO_SYSCALL ; 
 size_t BOOKE_IRQPRIO_WATCHDOG ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
#define  SPRN_DBCR0 155 
#define  SPRN_DBCR1 154 
#define  SPRN_DBSR 153 
#define  SPRN_DEAR 152 
#define  SPRN_ESR 151 
#define  SPRN_IVOR0 150 
#define  SPRN_IVOR1 149 
#define  SPRN_IVOR10 148 
#define  SPRN_IVOR11 147 
#define  SPRN_IVOR12 146 
#define  SPRN_IVOR13 145 
#define  SPRN_IVOR14 144 
#define  SPRN_IVOR15 143 
#define  SPRN_IVOR2 142 
#define  SPRN_IVOR3 141 
#define  SPRN_IVOR4 140 
#define  SPRN_IVOR5 139 
#define  SPRN_IVOR6 138 
#define  SPRN_IVOR7 137 
#define  SPRN_IVOR8 136 
#define  SPRN_IVOR9 135 
#define  SPRN_IVPR 134 
#define  SPRN_SPRG4 133 
#define  SPRN_SPRG5 132 
#define  SPRN_SPRG6 131 
#define  SPRN_SPRG7 130 
#define  SPRN_TCR 129 
#define  SPRN_TSR 128 
 int /*<<< orphan*/  kvmppc_emulate_dec (struct kvm_vcpu*) ; 

int kvmppc_booke_emulate_mtspr(struct kvm_vcpu *vcpu, int sprn, int rs)
{
	int emulated = EMULATE_DONE;

	switch (sprn) {
	case SPRN_DEAR:
		vcpu->arch.dear = vcpu->arch.gpr[rs]; break;
	case SPRN_ESR:
		vcpu->arch.esr = vcpu->arch.gpr[rs]; break;
	case SPRN_DBCR0:
		vcpu->arch.dbcr0 = vcpu->arch.gpr[rs]; break;
	case SPRN_DBCR1:
		vcpu->arch.dbcr1 = vcpu->arch.gpr[rs]; break;
	case SPRN_DBSR:
		vcpu->arch.dbsr &= ~vcpu->arch.gpr[rs]; break;
	case SPRN_TSR:
		vcpu->arch.tsr &= ~vcpu->arch.gpr[rs]; break;
	case SPRN_TCR:
		vcpu->arch.tcr = vcpu->arch.gpr[rs];
		kvmppc_emulate_dec(vcpu);
		break;

	/* Note: SPRG4-7 are user-readable. These values are
	 * loaded into the real SPRGs when resuming the
	 * guest. */
	case SPRN_SPRG4:
		vcpu->arch.sprg4 = vcpu->arch.gpr[rs]; break;
	case SPRN_SPRG5:
		vcpu->arch.sprg5 = vcpu->arch.gpr[rs]; break;
	case SPRN_SPRG6:
		vcpu->arch.sprg6 = vcpu->arch.gpr[rs]; break;
	case SPRN_SPRG7:
		vcpu->arch.sprg7 = vcpu->arch.gpr[rs]; break;

	case SPRN_IVPR:
		vcpu->arch.ivpr = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR0:
		vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR1:
		vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR2:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR3:
		vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR4:
		vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR5:
		vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR6:
		vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR7:
		vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR8:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR9:
		vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR10:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR11:
		vcpu->arch.ivor[BOOKE_IRQPRIO_FIT] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR12:
		vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR13:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR14:
		vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS] = vcpu->arch.gpr[rs];
		break;
	case SPRN_IVOR15:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG] = vcpu->arch.gpr[rs];
		break;

	default:
		emulated = EMULATE_FAIL;
	}

	return emulated;
}