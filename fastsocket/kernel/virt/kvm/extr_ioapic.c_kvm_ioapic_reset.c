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
struct kvm_ioapic {scalar_t__ id; scalar_t__ irr; scalar_t__ ioregsel; int /*<<< orphan*/  base_address; TYPE_2__* redirtbl; } ;
struct TYPE_3__ {int mask; } ;
struct TYPE_4__ {TYPE_1__ fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAPIC_DEFAULT_BASE_ADDRESS ; 
 int IOAPIC_NUM_PINS ; 
 int /*<<< orphan*/  update_handled_vectors (struct kvm_ioapic*) ; 

void kvm_ioapic_reset(struct kvm_ioapic *ioapic)
{
	int i;

	for (i = 0; i < IOAPIC_NUM_PINS; i++)
		ioapic->redirtbl[i].fields.mask = 1;
	ioapic->base_address = IOAPIC_DEFAULT_BASE_ADDRESS;
	ioapic->ioregsel = 0;
	ioapic->irr = 0;
	ioapic->id = 0;
	update_handled_vectors(ioapic);
}