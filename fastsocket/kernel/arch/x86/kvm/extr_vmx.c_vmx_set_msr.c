#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int u32 ;
struct vcpu_vmx {void* msr_guest_kernel_gs_base; } ;
struct shared_msr_entry {void* data; } ;
struct msr_data {int index; void* data; } ;
struct TYPE_3__ {void* pat; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int vmentry_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_FS_BASE ; 
 int /*<<< orphan*/  GUEST_GS_BASE ; 
 int /*<<< orphan*/  GUEST_IA32_PAT ; 
 int /*<<< orphan*/  GUEST_SYSENTER_CS ; 
 int /*<<< orphan*/  GUEST_SYSENTER_EIP ; 
 int /*<<< orphan*/  GUEST_SYSENTER_ESP ; 
#define  MSR_EFER 136 
#define  MSR_FS_BASE 135 
#define  MSR_GS_BASE 134 
#define  MSR_IA32_CR_PAT 133 
#define  MSR_IA32_SYSENTER_CS 132 
#define  MSR_IA32_SYSENTER_EIP 131 
#define  MSR_IA32_SYSENTER_ESP 130 
#define  MSR_IA32_TSC 129 
#define  MSR_KERNEL_GS_BASE 128 
 int VM_ENTRY_LOAD_IA32_PAT ; 
 struct shared_msr_entry* find_msr_entry (struct vcpu_vmx*,int) ; 
 int kvm_set_msr_common (struct kvm_vcpu*,struct msr_data*) ; 
 int /*<<< orphan*/  kvm_write_tsc (struct kvm_vcpu*,struct msr_data*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 TYPE_2__ vmcs_config ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vmx_load_host_state (struct vcpu_vmx*) ; 

__attribute__((used)) static int vmx_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct shared_msr_entry *msr;
	int ret = 0;
	u32 msr_index = msr_info->index;
	u64 data = msr_info->data;

	switch (msr_index) {
	case MSR_EFER:
		vmx_load_host_state(vmx);
		ret = kvm_set_msr_common(vcpu, msr_info);
		break;
#ifdef CONFIG_X86_64
	case MSR_FS_BASE:
		vmcs_writel(GUEST_FS_BASE, data);
		break;
	case MSR_GS_BASE:
		vmcs_writel(GUEST_GS_BASE, data);
		break;
	case MSR_KERNEL_GS_BASE:
		vmx_load_host_state(vmx);
		vmx->msr_guest_kernel_gs_base = data;
		break;
#endif
	case MSR_IA32_SYSENTER_CS:
		vmcs_write32(GUEST_SYSENTER_CS, data);
		break;
	case MSR_IA32_SYSENTER_EIP:
		vmcs_writel(GUEST_SYSENTER_EIP, data);
		break;
	case MSR_IA32_SYSENTER_ESP:
		vmcs_writel(GUEST_SYSENTER_ESP, data);
		break;
	case MSR_IA32_TSC:
		kvm_write_tsc(vcpu, msr_info);
		break;
	case MSR_IA32_CR_PAT:
		if (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT) {
			vmcs_write64(GUEST_IA32_PAT, data);
			vcpu->arch.pat = data;
			break;
		}
		/* Otherwise falls through to kvm_set_msr_common */
	default:
		msr = find_msr_entry(vmx, msr_index);
		if (msr) {
			vmx_load_host_state(vmx);
			msr->data = data;
			break;
		}
		ret = kvm_set_msr_common(vcpu, msr_info);
	}

	return ret;
}