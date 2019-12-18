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
struct TYPE_2__ {scalar_t__ vm_base; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  scalar_t__ addr ;

/* Variables and functions */
 scalar_t__ KVM_VM_DATA_BASE ; 

__attribute__((used)) static inline void *to_guest(struct kvm *kvm, void *addr)
{
	return (void *)((unsigned long)(addr) - kvm->arch.vm_base +
			KVM_VM_DATA_BASE);
}