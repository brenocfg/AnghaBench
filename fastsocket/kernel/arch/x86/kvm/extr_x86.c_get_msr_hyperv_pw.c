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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct kvm_vcpu {struct kvm* kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  hv_hypercall; int /*<<< orphan*/  hv_guest_os_id; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
#define  HV_X64_MSR_GUEST_OS_ID 129 
#define  HV_X64_MSR_HYPERCALL 128 
 int /*<<< orphan*/  pr_unimpl (struct kvm_vcpu*,char*,int) ; 

__attribute__((used)) static int get_msr_hyperv_pw(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata)
{
        u64 data = 0;
        struct kvm *kvm = vcpu->kvm;

        switch (msr) {
        case HV_X64_MSR_GUEST_OS_ID:
                data = kvm->arch.hv_guest_os_id;
                break;
        case HV_X64_MSR_HYPERCALL:
                data = kvm->arch.hv_hypercall;
                break;
        default:
                pr_unimpl(vcpu, "Hyper-V unhandled rdmsr: 0x%x\n", msr);
                return 1;
        }

        *pdata = data;
        return 0;
}