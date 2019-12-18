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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_2__ {int (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PFERR_USER_MASK ; 
 int kvm_read_guest_virt_helper (int /*<<< orphan*/ ,void*,unsigned int,struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_read_guest_virt(gva_t addr, void *val, unsigned int bytes,
			       struct kvm_vcpu *vcpu, u32 *error)
{
	u32 access = (kvm_x86_ops->get_cpl(vcpu) == 3) ? PFERR_USER_MASK : 0;
	return kvm_read_guest_virt_helper(addr, val, bytes, vcpu, access,
					  error);
}