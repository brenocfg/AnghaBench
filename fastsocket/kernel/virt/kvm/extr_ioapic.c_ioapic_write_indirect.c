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
struct TYPE_2__ {int mask; int /*<<< orphan*/  trig_mode; int /*<<< orphan*/  remote_irr; } ;
union kvm_ioapic_redirect_entry {int bits; TYPE_1__ fields; } ;
typedef  int u64 ;
typedef  int u32 ;
struct kvm_ioapic {int ioregsel; int id; int irr; int /*<<< orphan*/  kvm; union kvm_ioapic_redirect_entry* redirtbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAPIC_LEVEL_TRIG ; 
 unsigned int IOAPIC_NUM_PINS ; 
#define  IOAPIC_REG_APIC_ID 130 
#define  IOAPIC_REG_ARB_ID 129 
#define  IOAPIC_REG_VERSION 128 
 int /*<<< orphan*/  KVM_IRQCHIP_IOAPIC ; 
 int /*<<< orphan*/  ioapic_debug (char*,unsigned int,int) ; 
 int /*<<< orphan*/  ioapic_service (struct kvm_ioapic*,unsigned int) ; 
 int /*<<< orphan*/  kvm_fire_mask_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  update_handled_vectors (struct kvm_ioapic*) ; 

__attribute__((used)) static void ioapic_write_indirect(struct kvm_ioapic *ioapic, u32 val)
{
	unsigned index;
	bool mask_before, mask_after;
	union kvm_ioapic_redirect_entry *e;

	switch (ioapic->ioregsel) {
	case IOAPIC_REG_VERSION:
		/* Writes are ignored. */
		break;

	case IOAPIC_REG_APIC_ID:
		ioapic->id = (val >> 24) & 0xf;
		break;

	case IOAPIC_REG_ARB_ID:
		break;

	default:
		index = (ioapic->ioregsel - 0x10) >> 1;

		ioapic_debug("change redir index %x val %x\n", index, val);
		if (index >= IOAPIC_NUM_PINS)
			return;
		e = &ioapic->redirtbl[index];
		mask_before = e->fields.mask;
		if (ioapic->ioregsel & 1) {
			e->bits &= 0xffffffff;
			e->bits |= (u64) val << 32;
		} else {
			e->bits &= ~0xffffffffULL;
			e->bits |= (u32) val;
			e->fields.remote_irr = 0;
		}
		update_handled_vectors(ioapic);
		mask_after = e->fields.mask;
		if (mask_before != mask_after)
			kvm_fire_mask_notifiers(ioapic->kvm, KVM_IRQCHIP_IOAPIC, index, mask_after);
		if (e->fields.trig_mode == IOAPIC_LEVEL_TRIG
		    && ioapic->irr & (1 << index))
			ioapic_service(ioapic, index);
		break;
	}
}