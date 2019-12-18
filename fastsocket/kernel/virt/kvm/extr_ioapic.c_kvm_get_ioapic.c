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
struct kvm_ioapic_state {int dummy; } ;
struct kvm_ioapic {int /*<<< orphan*/  lock; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct kvm_ioapic* ioapic_irqchip (struct kvm*) ; 
 int /*<<< orphan*/  memcpy (struct kvm_ioapic_state*,struct kvm_ioapic*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvm_get_ioapic(struct kvm *kvm, struct kvm_ioapic_state *state)
{
	struct kvm_ioapic *ioapic = ioapic_irqchip(kvm);
	if (!ioapic)
		return -EINVAL;

	spin_lock(&ioapic->lock);
	memcpy(state, ioapic, sizeof(struct kvm_ioapic_state));
	spin_unlock(&ioapic->lock);
	return 0;
}