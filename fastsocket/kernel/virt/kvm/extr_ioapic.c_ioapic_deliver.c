#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int delivery_mode; int /*<<< orphan*/  trig_mode; scalar_t__ dest_mode; int /*<<< orphan*/  vector; int /*<<< orphan*/  dest_id; int /*<<< orphan*/  dest; } ;
union kvm_ioapic_redirect_entry {TYPE_1__ fields; } ;
struct kvm_lapic_irq {int delivery_mode; int level; int /*<<< orphan*/  dest_id; scalar_t__ dest_mode; scalar_t__ shorthand; int /*<<< orphan*/  trig_mode; int /*<<< orphan*/  vector; } ;
struct kvm_ioapic {TYPE_3__* kvm; union kvm_ioapic_redirect_entry* redirtbl; } ;
struct TYPE_6__ {TYPE_2__* bsp_vcpu; } ;
struct TYPE_5__ {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioapic_debug (char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvm_irq_delivery_to_apic (TYPE_3__*,int /*<<< orphan*/ *,struct kvm_lapic_irq*) ; 

__attribute__((used)) static int ioapic_deliver(struct kvm_ioapic *ioapic, int irq)
{
	union kvm_ioapic_redirect_entry *entry = &ioapic->redirtbl[irq];
	struct kvm_lapic_irq irqe;

	ioapic_debug("dest=%x dest_mode=%x delivery_mode=%x "
		     "vector=%x trig_mode=%x\n",
		     entry->fields.dest, entry->fields.dest_mode,
		     entry->fields.delivery_mode, entry->fields.vector,
		     entry->fields.trig_mode);

	irqe.dest_id = entry->fields.dest_id;
	irqe.vector = entry->fields.vector;
	irqe.dest_mode = entry->fields.dest_mode;
	irqe.trig_mode = entry->fields.trig_mode;
	irqe.delivery_mode = entry->fields.delivery_mode << 8;
	irqe.level = 1;
	irqe.shorthand = 0;

#ifdef CONFIG_X86
	/* Always delivery PIT interrupt to vcpu 0 */
	if (irq == 0) {
		irqe.dest_mode = 0; /* Physical mode. */
		/* need to read apic_id from apic regiest since
		 * it can be rewritten */
		irqe.dest_id = ioapic->kvm->bsp_vcpu->vcpu_id;
	}
#endif
	return kvm_irq_delivery_to_apic(ioapic->kvm, NULL, &irqe);
}