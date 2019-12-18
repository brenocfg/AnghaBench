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
struct kvm {int dummy; } ;

/* Variables and functions */
 int KVM_IRQFD_FLAG_DEASSIGN ; 
 int kvm_irqfd_assign (struct kvm*,int,int) ; 
 int kvm_irqfd_deassign (struct kvm*,int,int) ; 

int
kvm_irqfd(struct kvm *kvm, int fd, int gsi, int flags)
{
	if (flags & KVM_IRQFD_FLAG_DEASSIGN)
		return kvm_irqfd_deassign(kvm, fd, gsi);

	return kvm_irqfd_assign(kvm, fd, gsi);
}