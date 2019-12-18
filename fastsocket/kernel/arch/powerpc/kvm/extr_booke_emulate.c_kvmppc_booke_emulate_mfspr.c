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
struct TYPE_2__ {int /*<<< orphan*/ * ivor; int /*<<< orphan*/ * gpr; int /*<<< orphan*/  dbsr; int /*<<< orphan*/  dbcr1; int /*<<< orphan*/  dbcr0; int /*<<< orphan*/  esr; int /*<<< orphan*/  dear; int /*<<< orphan*/  ivpr; } ;
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
#define  SPRN_DBCR0 149 
#define  SPRN_DBCR1 148 
#define  SPRN_DBSR 147 
#define  SPRN_DEAR 146 
#define  SPRN_ESR 145 
#define  SPRN_IVOR0 144 
#define  SPRN_IVOR1 143 
#define  SPRN_IVOR10 142 
#define  SPRN_IVOR11 141 
#define  SPRN_IVOR12 140 
#define  SPRN_IVOR13 139 
#define  SPRN_IVOR14 138 
#define  SPRN_IVOR15 137 
#define  SPRN_IVOR2 136 
#define  SPRN_IVOR3 135 
#define  SPRN_IVOR4 134 
#define  SPRN_IVOR5 133 
#define  SPRN_IVOR6 132 
#define  SPRN_IVOR7 131 
#define  SPRN_IVOR8 130 
#define  SPRN_IVOR9 129 
#define  SPRN_IVPR 128 

int kvmppc_booke_emulate_mfspr(struct kvm_vcpu *vcpu, int sprn, int rt)
{
	int emulated = EMULATE_DONE;

	switch (sprn) {
	case SPRN_IVPR:
		vcpu->arch.gpr[rt] = vcpu->arch.ivpr; break;
	case SPRN_DEAR:
		vcpu->arch.gpr[rt] = vcpu->arch.dear; break;
	case SPRN_ESR:
		vcpu->arch.gpr[rt] = vcpu->arch.esr; break;
	case SPRN_DBCR0:
		vcpu->arch.gpr[rt] = vcpu->arch.dbcr0; break;
	case SPRN_DBCR1:
		vcpu->arch.gpr[rt] = vcpu->arch.dbcr1; break;
	case SPRN_DBSR:
		vcpu->arch.gpr[rt] = vcpu->arch.dbsr; break;

	case SPRN_IVOR0:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL];
		break;
	case SPRN_IVOR1:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK];
		break;
	case SPRN_IVOR2:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE];
		break;
	case SPRN_IVOR3:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE];
		break;
	case SPRN_IVOR4:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL];
		break;
	case SPRN_IVOR5:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT];
		break;
	case SPRN_IVOR6:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM];
		break;
	case SPRN_IVOR7:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL];
		break;
	case SPRN_IVOR8:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL];
		break;
	case SPRN_IVOR9:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL];
		break;
	case SPRN_IVOR10:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER];
		break;
	case SPRN_IVOR11:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_FIT];
		break;
	case SPRN_IVOR12:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG];
		break;
	case SPRN_IVOR13:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS];
		break;
	case SPRN_IVOR14:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS];
		break;
	case SPRN_IVOR15:
		vcpu->arch.gpr[rt] = vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG];
		break;

	default:
		emulated = EMULATE_FAIL;
	}

	return emulated;
}