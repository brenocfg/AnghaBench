#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int GUEST_INTR_STATE_MOV_SS ; 
 int GUEST_INTR_STATE_STI ; 
 int X86_SHADOW_INT_MOV_SS ; 
 int X86_SHADOW_INT_STI ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vmx_get_interrupt_shadow(struct kvm_vcpu *vcpu, int mask)
{
	u32 interruptibility = vmcs_read32(GUEST_INTERRUPTIBILITY_INFO);
	int ret = 0;

	if (interruptibility & GUEST_INTR_STATE_STI)
		ret |= X86_SHADOW_INT_STI;
	if (interruptibility & GUEST_INTR_STATE_MOV_SS)
		ret |= X86_SHADOW_INT_MOV_SS;

	return ret & mask;
}