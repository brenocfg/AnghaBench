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
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct TYPE_3__ {scalar_t__ is_sn2; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  _IA64_REG_AR_ITC ; 
 unsigned long ia64_getreg (int /*<<< orphan*/ ) ; 
 unsigned long rtc_time () ; 

__attribute__((used)) static unsigned long kvm_get_itc(struct kvm_vcpu *vcpu)
{
#if defined(CONFIG_IA64_SGI_SN2) || defined(CONFIG_IA64_GENERIC)
	if (vcpu->kvm->arch.is_sn2)
		return rtc_time();
	else
#endif
		return ia64_getreg(_IA64_REG_AR_ITC);
}