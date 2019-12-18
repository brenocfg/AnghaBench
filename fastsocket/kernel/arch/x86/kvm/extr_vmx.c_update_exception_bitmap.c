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
typedef  unsigned int u32 ;
struct kvm_vcpu {int guest_debug; scalar_t__ fpu_active; } ;
struct TYPE_3__ {scalar_t__ vm86_active; } ;
struct TYPE_4__ {TYPE_1__ rmode; } ;

/* Variables and functions */
 unsigned int BP_VECTOR ; 
 unsigned int DB_VECTOR ; 
 int /*<<< orphan*/  EXCEPTION_BITMAP ; 
 int KVM_GUESTDBG_ENABLE ; 
 int KVM_GUESTDBG_USE_SW_BP ; 
 unsigned int MC_VECTOR ; 
 unsigned int NM_VECTOR ; 
 unsigned int PF_VECTOR ; 
 unsigned int UD_VECTOR ; 
 scalar_t__ enable_ept ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void update_exception_bitmap(struct kvm_vcpu *vcpu)
{
	u32 eb;

	eb = (1u << PF_VECTOR) | (1u << UD_VECTOR) | (1u << MC_VECTOR)
		| (1u << NM_VECTOR);
	/*
	 * Unconditionally intercept #DB so we can maintain dr6 without
	 * reading it every exit.
	 */
	eb |= 1u << DB_VECTOR;
	if (vcpu->guest_debug & KVM_GUESTDBG_ENABLE) {
		if (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			eb |= 1u << BP_VECTOR;
	}
	if (to_vmx(vcpu)->rmode.vm86_active)
		eb = ~0;
	if (enable_ept)
		eb &= ~(1u << PF_VECTOR); /* bypass_guest_pf = 0 */
	if (vcpu->fpu_active)
		eb &= ~(1u << NM_VECTOR);
	vmcs_write32(EXCEPTION_BITMAP, eb);
}