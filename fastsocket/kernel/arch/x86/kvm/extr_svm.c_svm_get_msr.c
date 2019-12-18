#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_12__ {int hsave_msr; TYPE_2__* hsave; } ;
struct vcpu_svm {int sysenter_eip; int sysenter_esp; TYPE_6__ nested; TYPE_5__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_10__ {int star; int lstar; int cstar; int kernel_gs_base; int sfmask; int sysenter_cs; int dbgctl; int br_from; int br_to; int last_excp_from; int last_excp_to; } ;
struct TYPE_9__ {int tsc_offset; } ;
struct TYPE_11__ {TYPE_4__ save; TYPE_3__ control; } ;
struct TYPE_7__ {int tsc_offset; } ;
struct TYPE_8__ {TYPE_1__ control; } ;

/* Variables and functions */
#define  MSR_CSTAR 144 
#define  MSR_IA32_DEBUGCTLMSR 143 
#define  MSR_IA32_LASTBRANCHFROMIP 142 
#define  MSR_IA32_LASTBRANCHTOIP 141 
#define  MSR_IA32_LASTINTFROMIP 140 
#define  MSR_IA32_LASTINTTOIP 139 
#define  MSR_IA32_SYSENTER_CS 138 
#define  MSR_IA32_SYSENTER_EIP 137 
#define  MSR_IA32_SYSENTER_ESP 136 
#define  MSR_IA32_TSC 135 
#define  MSR_IA32_UCODE_REV 134 
#define  MSR_K6_STAR 133 
#define  MSR_KERNEL_GS_BASE 132 
#define  MSR_LSTAR 131 
#define  MSR_SYSCALL_MASK 130 
#define  MSR_VM_CR 129 
#define  MSR_VM_HSAVE_PA 128 
 int /*<<< orphan*/  is_nested (struct vcpu_svm*) ; 
 int kvm_get_msr_common (struct kvm_vcpu*,unsigned int,int*) ; 
 int /*<<< orphan*/  native_read_tsc () ; 
 int svm_scale_tsc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static int svm_get_msr(struct kvm_vcpu *vcpu, unsigned ecx, u64 *data)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	switch (ecx) {
	case MSR_IA32_TSC: {
		u64 tsc_offset;

		if (is_nested(svm))
			tsc_offset = svm->nested.hsave->control.tsc_offset;
		else
			tsc_offset = svm->vmcb->control.tsc_offset;

		*data = tsc_offset + svm_scale_tsc(vcpu, native_read_tsc());
		break;
	}
	case MSR_K6_STAR:
		*data = svm->vmcb->save.star;
		break;
#ifdef CONFIG_X86_64
	case MSR_LSTAR:
		*data = svm->vmcb->save.lstar;
		break;
	case MSR_CSTAR:
		*data = svm->vmcb->save.cstar;
		break;
	case MSR_KERNEL_GS_BASE:
		*data = svm->vmcb->save.kernel_gs_base;
		break;
	case MSR_SYSCALL_MASK:
		*data = svm->vmcb->save.sfmask;
		break;
#endif
	case MSR_IA32_SYSENTER_CS:
		*data = svm->vmcb->save.sysenter_cs;
		break;
	case MSR_IA32_SYSENTER_EIP:
		*data = svm->sysenter_eip;
		break;
	case MSR_IA32_SYSENTER_ESP:
		*data = svm->sysenter_esp;
		break;
	/* Nobody will change the following 5 values in the VMCB so
	   we can safely return them on rdmsr. They will always be 0
	   until LBRV is implemented. */
	case MSR_IA32_DEBUGCTLMSR:
		*data = svm->vmcb->save.dbgctl;
		break;
	case MSR_IA32_LASTBRANCHFROMIP:
		*data = svm->vmcb->save.br_from;
		break;
	case MSR_IA32_LASTBRANCHTOIP:
		*data = svm->vmcb->save.br_to;
		break;
	case MSR_IA32_LASTINTFROMIP:
		*data = svm->vmcb->save.last_excp_from;
		break;
	case MSR_IA32_LASTINTTOIP:
		*data = svm->vmcb->save.last_excp_to;
		break;
	case MSR_VM_HSAVE_PA:
		*data = svm->nested.hsave_msr;
		break;
	case MSR_VM_CR:
		*data = 0;
		break;
	case MSR_IA32_UCODE_REV:
		*data = 0x01000065;
		break;
	default:
		return kvm_get_msr_common(vcpu, ecx, data);
	}
	return 0;
}