#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct kvm_pt_regs {int dummy; } ;
struct TYPE_37__ {unsigned long inst; } ;
typedef  TYPE_1__ INST64 ;

/* Variables and functions */
#define  EVENT_BSW_0 167 
#define  EVENT_BSW_1 166 
#define  EVENT_COVER 165 
#define  EVENT_ITC_D 164 
#define  EVENT_ITC_I 163 
#define  EVENT_ITR_D 162 
#define  EVENT_ITR_I 161 
#define  EVENT_MOV_FROM_AR 160 
#define  EVENT_MOV_FROM_CPUID 159 
#define  EVENT_MOV_FROM_CR 158 
#define  EVENT_MOV_FROM_DBR 157 
#define  EVENT_MOV_FROM_IBR 156 
#define  EVENT_MOV_FROM_PKR 155 
#define  EVENT_MOV_FROM_PMC 154 
#define  EVENT_MOV_FROM_PSR 153 
#define  EVENT_MOV_FROM_RR 152 
#define  EVENT_MOV_TO_AR 151 
#define  EVENT_MOV_TO_AR_IMM 150 
#define  EVENT_MOV_TO_CR 149 
#define  EVENT_MOV_TO_DBR 148 
#define  EVENT_MOV_TO_IBR 147 
#define  EVENT_MOV_TO_PKR 146 
#define  EVENT_MOV_TO_PMC 145 
#define  EVENT_MOV_TO_PMD 144 
#define  EVENT_MOV_TO_PSR 143 
#define  EVENT_MOV_TO_RR 142 
#define  EVENT_PTC_E 141 
#define  EVENT_PTC_G 140 
#define  EVENT_PTC_GA 139 
#define  EVENT_PTC_L 138 
#define  EVENT_PTR_D 137 
#define  EVENT_PTR_I 136 
#define  EVENT_RFI 135 
#define  EVENT_RSM 134 
#define  EVENT_SSM 133 
#define  EVENT_TAK 132 
#define  EVENT_THASH 131 
#define  EVENT_TPA 130 
#define  EVENT_TTAG 129 
#define  EVENT_VMSW 128 
 unsigned long IA64_FAULT ; 
 unsigned long IA64_NO_FAULT ; 
 unsigned long VMX (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  kvm_itc_d (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_itc_i (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_itr_d (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_itr_i (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_ar_reg (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_cpuid (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_cr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_dbr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_ibr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_pkr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_pmc (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_psr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_from_rr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_ar_imm (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_ar_reg (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_cr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_dbr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_ibr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_pkr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_pmc (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_pmd (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_psr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_mov_to_rr (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ptc_e (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ptc_g (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ptc_ga (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ptc_l (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ptr_d (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ptr_i (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_rsm (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ssm (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_tak (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_thash (struct kvm_vcpu*,TYPE_1__) ; 
 unsigned long kvm_tpa (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  kvm_ttag (struct kvm_vcpu*,TYPE_1__) ; 
 int /*<<< orphan*/  prepare_if_physical_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  recover_if_physical_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_bsw0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_bsw1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_cover (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_increment_iip (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_rfi (struct kvm_vcpu*) ; 

void kvm_emulate(struct kvm_vcpu *vcpu, struct kvm_pt_regs *regs)
{
	unsigned long status, cause, opcode ;
	INST64 inst;

	status = IA64_NO_FAULT;
	cause = VMX(vcpu, cause);
	opcode = VMX(vcpu, opcode);
	inst.inst = opcode;
	/*
	 * Switch to actual virtual rid in rr0 and rr4,
	 * which is required by some tlb related instructions.
	 */
	prepare_if_physical_mode(vcpu);

	switch (cause) {
	case EVENT_RSM:
		kvm_rsm(vcpu, inst);
		break;
	case EVENT_SSM:
		kvm_ssm(vcpu, inst);
		break;
	case EVENT_MOV_TO_PSR:
		kvm_mov_to_psr(vcpu, inst);
		break;
	case EVENT_MOV_FROM_PSR:
		kvm_mov_from_psr(vcpu, inst);
		break;
	case EVENT_MOV_FROM_CR:
		kvm_mov_from_cr(vcpu, inst);
		break;
	case EVENT_MOV_TO_CR:
		kvm_mov_to_cr(vcpu, inst);
		break;
	case EVENT_BSW_0:
		vcpu_bsw0(vcpu);
		break;
	case EVENT_BSW_1:
		vcpu_bsw1(vcpu);
		break;
	case EVENT_COVER:
		vcpu_cover(vcpu);
		break;
	case EVENT_RFI:
		vcpu_rfi(vcpu);
		break;
	case EVENT_ITR_D:
		kvm_itr_d(vcpu, inst);
		break;
	case EVENT_ITR_I:
		kvm_itr_i(vcpu, inst);
		break;
	case EVENT_PTR_D:
		kvm_ptr_d(vcpu, inst);
		break;
	case EVENT_PTR_I:
		kvm_ptr_i(vcpu, inst);
		break;
	case EVENT_ITC_D:
		kvm_itc_d(vcpu, inst);
		break;
	case EVENT_ITC_I:
		kvm_itc_i(vcpu, inst);
		break;
	case EVENT_PTC_L:
		kvm_ptc_l(vcpu, inst);
		break;
	case EVENT_PTC_G:
		kvm_ptc_g(vcpu, inst);
		break;
	case EVENT_PTC_GA:
		kvm_ptc_ga(vcpu, inst);
		break;
	case EVENT_PTC_E:
		kvm_ptc_e(vcpu, inst);
		break;
	case EVENT_MOV_TO_RR:
		kvm_mov_to_rr(vcpu, inst);
		break;
	case EVENT_MOV_FROM_RR:
		kvm_mov_from_rr(vcpu, inst);
		break;
	case EVENT_THASH:
		kvm_thash(vcpu, inst);
		break;
	case EVENT_TTAG:
		kvm_ttag(vcpu, inst);
		break;
	case EVENT_TPA:
		status = kvm_tpa(vcpu, inst);
		break;
	case EVENT_TAK:
		kvm_tak(vcpu, inst);
		break;
	case EVENT_MOV_TO_AR_IMM:
		kvm_mov_to_ar_imm(vcpu, inst);
		break;
	case EVENT_MOV_TO_AR:
		kvm_mov_to_ar_reg(vcpu, inst);
		break;
	case EVENT_MOV_FROM_AR:
		kvm_mov_from_ar_reg(vcpu, inst);
		break;
	case EVENT_MOV_TO_DBR:
		kvm_mov_to_dbr(vcpu, inst);
		break;
	case EVENT_MOV_TO_IBR:
		kvm_mov_to_ibr(vcpu, inst);
		break;
	case EVENT_MOV_TO_PMC:
		kvm_mov_to_pmc(vcpu, inst);
		break;
	case EVENT_MOV_TO_PMD:
		kvm_mov_to_pmd(vcpu, inst);
		break;
	case EVENT_MOV_TO_PKR:
		kvm_mov_to_pkr(vcpu, inst);
		break;
	case EVENT_MOV_FROM_DBR:
		kvm_mov_from_dbr(vcpu, inst);
		break;
	case EVENT_MOV_FROM_IBR:
		kvm_mov_from_ibr(vcpu, inst);
		break;
	case EVENT_MOV_FROM_PMC:
		kvm_mov_from_pmc(vcpu, inst);
		break;
	case EVENT_MOV_FROM_PKR:
		kvm_mov_from_pkr(vcpu, inst);
		break;
	case EVENT_MOV_FROM_CPUID:
		kvm_mov_from_cpuid(vcpu, inst);
		break;
	case EVENT_VMSW:
		status = IA64_FAULT;
		break;
	default:
		break;
	};
	/*Assume all status is NO_FAULT ?*/
	if (status == IA64_NO_FAULT && cause != EVENT_RFI)
		vcpu_increment_iip(vcpu);

	recover_if_physical_mode(vcpu);
}