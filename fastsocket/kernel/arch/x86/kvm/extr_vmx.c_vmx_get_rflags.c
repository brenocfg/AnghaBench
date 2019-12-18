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
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {unsigned long save_rflags; scalar_t__ vm86_active; } ;
struct TYPE_4__ {TYPE_1__ rmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_RFLAGS ; 
 unsigned long RMODE_GUEST_OWNED_EFLAGS_BITS ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long vmx_get_rflags(struct kvm_vcpu *vcpu)
{
	unsigned long rflags, save_rflags;

	rflags = vmcs_readl(GUEST_RFLAGS);
	if (to_vmx(vcpu)->rmode.vm86_active) {
		rflags &= RMODE_GUEST_OWNED_EFLAGS_BITS;
		save_rflags = to_vmx(vcpu)->rmode.save_rflags;
		rflags |= save_rflags & ~RMODE_GUEST_OWNED_EFLAGS_BITS;
	}
	return rflags;
}