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
struct hpet_data {int* hd_irq; size_t hd_nirqs; void* hd_address; int /*<<< orphan*/  hd_phys_address; } ;
struct acpi_resource_fixed_memory32 {int /*<<< orphan*/  address; } ;
struct acpi_resource_extended_irq {int interrupt_count; int /*<<< orphan*/  polarity; int /*<<< orphan*/  triggering; int /*<<< orphan*/ * interrupts; } ;
struct acpi_resource_address64 {int /*<<< orphan*/  address_length; int /*<<< orphan*/  minimum; } ;
struct TYPE_2__ {struct acpi_resource_extended_irq extended_irq; struct acpi_resource_fixed_memory32 fixed_memory32; } ;
struct acpi_resource {scalar_t__ type; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_TYPE_EXTENDED_IRQ ; 
 scalar_t__ ACPI_RESOURCE_TYPE_FIXED_MEMORY32 ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  HPET_RANGE_SIZE ; 
 int acpi_register_gsi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_resource_to_address64 (struct acpi_resource*,struct acpi_resource_address64*) ; 
 scalar_t__ hpet_is_known (struct hpet_data*) ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 

__attribute__((used)) static acpi_status hpet_resources(struct acpi_resource *res, void *data)
{
	struct hpet_data *hdp;
	acpi_status status;
	struct acpi_resource_address64 addr;

	hdp = data;

	status = acpi_resource_to_address64(res, &addr);

	if (ACPI_SUCCESS(status)) {
		hdp->hd_phys_address = addr.minimum;
		hdp->hd_address = ioremap(addr.minimum, addr.address_length);

		if (hpet_is_known(hdp)) {
			iounmap(hdp->hd_address);
			return AE_ALREADY_EXISTS;
		}
	} else if (res->type == ACPI_RESOURCE_TYPE_FIXED_MEMORY32) {
		struct acpi_resource_fixed_memory32 *fixmem32;

		fixmem32 = &res->data.fixed_memory32;
		if (!fixmem32)
			return AE_NO_MEMORY;

		hdp->hd_phys_address = fixmem32->address;
		hdp->hd_address = ioremap(fixmem32->address,
						HPET_RANGE_SIZE);

		if (hpet_is_known(hdp)) {
			iounmap(hdp->hd_address);
			return AE_ALREADY_EXISTS;
		}
	} else if (res->type == ACPI_RESOURCE_TYPE_EXTENDED_IRQ) {
		struct acpi_resource_extended_irq *irqp;
		int i, irq;

		irqp = &res->data.extended_irq;

		for (i = 0; i < irqp->interrupt_count; i++) {
			irq = acpi_register_gsi(NULL, irqp->interrupts[i],
				      irqp->triggering, irqp->polarity);
			if (irq < 0)
				return AE_ERROR;

			hdp->hd_irq[hdp->hd_nirqs] = irq;
			hdp->hd_nirqs++;
		}
	}

	return AE_OK;
}