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
struct kvm {int dummy; } ;
struct TYPE_2__ {struct kvm_vcpu* (* vcpu_create ) (struct kvm*,unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__* kvm_x86_ops ; 
 struct kvm_vcpu* stub1 (struct kvm*,unsigned int) ; 

struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm,
						unsigned int id)
{
	return kvm_x86_ops->vcpu_create(kvm, id);
}