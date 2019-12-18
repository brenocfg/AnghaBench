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
typedef  int ulong ;
struct TYPE_2__ {int msr; int srr0; int pc; int srr1; int ivpr; int* ivor; int /*<<< orphan*/  pending_exceptions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  BOOKE_IRQPRIO_ALIGNMENT 146 
#define  BOOKE_IRQPRIO_AP_UNAVAIL 145 
#define  BOOKE_IRQPRIO_CRITICAL 144 
#define  BOOKE_IRQPRIO_DATA_STORAGE 143 
#define  BOOKE_IRQPRIO_DEBUG 142 
#define  BOOKE_IRQPRIO_DECREMENTER 141 
#define  BOOKE_IRQPRIO_DTLB_MISS 140 
#define  BOOKE_IRQPRIO_EXTERNAL 139 
#define  BOOKE_IRQPRIO_FIT 138 
#define  BOOKE_IRQPRIO_FP_UNAVAIL 137 
#define  BOOKE_IRQPRIO_INST_STORAGE 136 
#define  BOOKE_IRQPRIO_ITLB_MISS 135 
#define  BOOKE_IRQPRIO_MACHINE_CHECK 134 
#define  BOOKE_IRQPRIO_PROGRAM 133 
#define  BOOKE_IRQPRIO_SPE_FP_DATA 132 
#define  BOOKE_IRQPRIO_SPE_FP_ROUND 131 
#define  BOOKE_IRQPRIO_SPE_UNAVAIL 130 
#define  BOOKE_IRQPRIO_SYSCALL 129 
#define  BOOKE_IRQPRIO_WATCHDOG 128 
 int MSR_CE ; 
 int MSR_DE ; 
 int MSR_EE ; 
 int MSR_ME ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int kvmppc_booke_irqprio_deliver(struct kvm_vcpu *vcpu,
                                        unsigned int priority)
{
	int allowed = 0;
	ulong msr_mask;

	switch (priority) {
	case BOOKE_IRQPRIO_PROGRAM:
	case BOOKE_IRQPRIO_DTLB_MISS:
	case BOOKE_IRQPRIO_ITLB_MISS:
	case BOOKE_IRQPRIO_SYSCALL:
	case BOOKE_IRQPRIO_DATA_STORAGE:
	case BOOKE_IRQPRIO_INST_STORAGE:
	case BOOKE_IRQPRIO_FP_UNAVAIL:
	case BOOKE_IRQPRIO_SPE_UNAVAIL:
	case BOOKE_IRQPRIO_SPE_FP_DATA:
	case BOOKE_IRQPRIO_SPE_FP_ROUND:
	case BOOKE_IRQPRIO_AP_UNAVAIL:
	case BOOKE_IRQPRIO_ALIGNMENT:
		allowed = 1;
		msr_mask = MSR_CE|MSR_ME|MSR_DE;
		break;
	case BOOKE_IRQPRIO_CRITICAL:
	case BOOKE_IRQPRIO_WATCHDOG:
		allowed = vcpu->arch.msr & MSR_CE;
		msr_mask = MSR_ME;
		break;
	case BOOKE_IRQPRIO_MACHINE_CHECK:
		allowed = vcpu->arch.msr & MSR_ME;
		msr_mask = 0;
		break;
	case BOOKE_IRQPRIO_EXTERNAL:
	case BOOKE_IRQPRIO_DECREMENTER:
	case BOOKE_IRQPRIO_FIT:
		allowed = vcpu->arch.msr & MSR_EE;
		msr_mask = MSR_CE|MSR_ME|MSR_DE;
		break;
	case BOOKE_IRQPRIO_DEBUG:
		allowed = vcpu->arch.msr & MSR_DE;
		msr_mask = MSR_ME;
		break;
	}

	if (allowed) {
		vcpu->arch.srr0 = vcpu->arch.pc;
		vcpu->arch.srr1 = vcpu->arch.msr;
		vcpu->arch.pc = vcpu->arch.ivpr | vcpu->arch.ivor[priority];
		kvmppc_set_msr(vcpu, vcpu->arch.msr & msr_mask);

		clear_bit(priority, &vcpu->arch.pending_exceptions);
	}

	return allowed;
}