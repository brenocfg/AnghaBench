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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int ipb; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int __diag_ipl_functions (struct kvm_vcpu*) ; 
 int __diag_time_slice_end (struct kvm_vcpu*) ; 
 int __diag_time_slice_end_directed (struct kvm_vcpu*) ; 

int kvm_s390_handle_diag(struct kvm_vcpu *vcpu)
{
	int code = (vcpu->arch.sie_block->ipb & 0xfff0000) >> 16;

	switch (code) {
	case 0x44:
		return __diag_time_slice_end(vcpu);
	case 0x9c:
		return __diag_time_slice_end_directed(vcpu);
	case 0x308:
		return __diag_ipl_functions(vcpu);
	default:
		return -ENOTSUPP;
	}
}