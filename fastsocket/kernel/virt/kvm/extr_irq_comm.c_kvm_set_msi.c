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
struct kvm_lapic_irq {int dest_id; int vector; int dest_mode; int trig_mode; int delivery_mode; int level; scalar_t__ shorthand; } ;
struct TYPE_2__ {int address_lo; int data; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ msi; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int MSI_ADDR_DEST_ID_MASK ; 
 int MSI_ADDR_DEST_ID_SHIFT ; 
 int MSI_ADDR_DEST_MODE_SHIFT ; 
 int MSI_DATA_TRIGGER_SHIFT ; 
 int MSI_DATA_VECTOR_MASK ; 
 int MSI_DATA_VECTOR_SHIFT ; 
 int kvm_irq_delivery_to_apic (struct kvm*,int /*<<< orphan*/ *,struct kvm_lapic_irq*) ; 
 int /*<<< orphan*/  trace_kvm_msi_set_irq (int,int) ; 

int kvm_set_msi(struct kvm_kernel_irq_routing_entry *e,
		struct kvm *kvm, int irq_source_id, int level)
{
	struct kvm_lapic_irq irq;

	if (!level)
		return -1;

	trace_kvm_msi_set_irq(e->msi.address_lo, e->msi.data);

	irq.dest_id = (e->msi.address_lo &
			MSI_ADDR_DEST_ID_MASK) >> MSI_ADDR_DEST_ID_SHIFT;
	irq.vector = (e->msi.data &
			MSI_DATA_VECTOR_MASK) >> MSI_DATA_VECTOR_SHIFT;
	irq.dest_mode = (1 << MSI_ADDR_DEST_MODE_SHIFT) & e->msi.address_lo;
	irq.trig_mode = (1 << MSI_DATA_TRIGGER_SHIFT) & e->msi.data;
	irq.delivery_mode = e->msi.data & 0x700;
	irq.level = 1;
	irq.shorthand = 0;

	/* TODO Deal with RH bit of MSI message address */
	return kvm_irq_delivery_to_apic(kvm, NULL, &irq);
}