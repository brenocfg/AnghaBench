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
typedef  int ulong ;
struct TYPE_3__ {int cr4_guest_owned_bits; int cr4; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* decache_cr4_guest_bits ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static inline ulong kvm_read_cr4_bits(struct kvm_vcpu *vcpu, ulong mask)
{
	if (mask & vcpu->arch.cr4_guest_owned_bits)
		kvm_x86_ops->decache_cr4_guest_bits(vcpu);
	return vcpu->arch.cr4 & mask;
}