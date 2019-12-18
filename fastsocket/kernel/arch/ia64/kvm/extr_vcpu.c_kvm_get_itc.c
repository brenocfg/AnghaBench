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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_sn2; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ KVM_VM_BASE ; 
 long* SN_RTC_BASE ; 
 int /*<<< orphan*/  _IA64_REG_AR_ITC ; 
 long ia64_getreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long kvm_get_itc(struct kvm_vcpu *vcpu)
{
#if defined(CONFIG_IA64_SGI_SN2) || defined(CONFIG_IA64_GENERIC)
	struct kvm *kvm = (struct kvm *)KVM_VM_BASE;

	if (kvm->arch.is_sn2)
		return (*SN_RTC_BASE);
	else
#endif
		return ia64_getreg(_IA64_REG_AR_ITC);
}