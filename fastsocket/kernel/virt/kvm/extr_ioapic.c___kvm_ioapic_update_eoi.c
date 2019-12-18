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
struct TYPE_2__ {int vector; int trig_mode; int /*<<< orphan*/  mask; scalar_t__ remote_irr; } ;
union kvm_ioapic_redirect_entry {TYPE_1__ fields; } ;
struct kvm_ioapic {int irr; int /*<<< orphan*/  lock; int /*<<< orphan*/  kvm; union kvm_ioapic_redirect_entry* redirtbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int IOAPIC_LEVEL_TRIG ; 
 int IOAPIC_NUM_PINS ; 
 int /*<<< orphan*/  KVM_IRQCHIP_IOAPIC ; 
 int /*<<< orphan*/  ioapic_service (struct kvm_ioapic*,int) ; 
 int /*<<< orphan*/  kvm_notify_acked_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __kvm_ioapic_update_eoi(struct kvm_ioapic *ioapic, int vector,
				     int trigger_mode)
{
	int i;

	for (i = 0; i < IOAPIC_NUM_PINS; i++) {
		union kvm_ioapic_redirect_entry *ent = &ioapic->redirtbl[i];

		if (ent->fields.vector != vector)
			continue;

		/*
		 * We are dropping lock while calling ack notifiers because ack
		 * notifier callbacks for assigned devices call into IOAPIC
		 * recursively. Since remote_irr is cleared only after call
		 * to notifiers if the same vector will be delivered while lock
		 * is dropped it will be put into irr and will be delivered
		 * after ack notifier returns.
		 */
		spin_unlock(&ioapic->lock);
		kvm_notify_acked_irq(ioapic->kvm, KVM_IRQCHIP_IOAPIC, i);
		spin_lock(&ioapic->lock);

		if (trigger_mode != IOAPIC_LEVEL_TRIG)
			continue;

		ASSERT(ent->fields.trig_mode == IOAPIC_LEVEL_TRIG);
		ent->fields.remote_irr = 0;
		if (!ent->fields.mask && (ioapic->irr & (1 << i)))
			ioapic_service(ioapic, i);
	}
}