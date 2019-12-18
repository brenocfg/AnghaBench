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
struct TYPE_4__ {int /*<<< orphan*/  sn_rtc_tr_slot; int /*<<< orphan*/  vm_tr_slot; int /*<<< orphan*/  vmm_tr_slot; } ;
struct kvm_vcpu {TYPE_2__ arch; struct kvm* kvm; } ;
struct TYPE_3__ {scalar_t__ is_sn2; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_ptr_entry (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_purge_vmm_mapping(struct kvm_vcpu *vcpu)
{
	struct kvm *kvm = vcpu->kvm;
	ia64_ptr_entry(0x3, vcpu->arch.vmm_tr_slot);
	ia64_ptr_entry(0x3, vcpu->arch.vm_tr_slot);
#if defined(CONFIG_IA64_SGI_SN2) || defined(CONFIG_IA64_GENERIC)
	if (kvm->arch.is_sn2)
		ia64_ptr_entry(0x3, vcpu->arch.sn_rtc_tr_slot);
#endif
}