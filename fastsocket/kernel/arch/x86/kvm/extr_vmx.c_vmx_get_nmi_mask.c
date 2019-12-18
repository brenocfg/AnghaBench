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
struct TYPE_2__ {int soft_vnmi_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int GUEST_INTR_STATE_NMI ; 
 int /*<<< orphan*/  cpu_has_virtual_nmis () ; 
 TYPE_1__* to_vmx (struct kvm_vcpu*) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vmx_get_nmi_mask(struct kvm_vcpu *vcpu)
{
	if (!cpu_has_virtual_nmis())
		return to_vmx(vcpu)->soft_vnmi_blocked;
	else
		return !!(vmcs_read32(GUEST_INTERRUPTIBILITY_INFO) &
			  GUEST_INTR_STATE_NMI);
}