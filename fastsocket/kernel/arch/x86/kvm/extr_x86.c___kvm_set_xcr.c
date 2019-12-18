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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int xcr0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 scalar_t__ XCR_XFEATURE_ENABLED_MASK ; 
 int XSTATE_FP ; 
 int XSTATE_SSE ; 
 int XSTATE_YMM ; 
 int host_xcr0 ; 
 int /*<<< orphan*/  kvm_put_guest_xcr0 (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

int __kvm_set_xcr(struct kvm_vcpu *vcpu, u32 index, u64 xcr)
{
	u64 xcr0;

	/* Only support XCR_XFEATURE_ENABLED_MASK(xcr0) now  */
	if (index != XCR_XFEATURE_ENABLED_MASK)
		return 1;
	xcr0 = xcr;
	if (kvm_x86_ops->get_cpl(vcpu) != 0)
		return 1;
	if (!(xcr0 & XSTATE_FP))
		return 1;
	if ((xcr0 & XSTATE_YMM) && !(xcr0 & XSTATE_SSE))
		return 1;
	if (xcr0 & ~host_xcr0)
		return 1;
	kvm_put_guest_xcr0(vcpu);
	vcpu->arch.xcr0 = xcr0;
	return 0;
}