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
struct acpi_resource_irq {unsigned int* interrupts; } ;
struct TYPE_2__ {struct acpi_resource_irq irq; } ;
struct acpi_resource {scalar_t__ type; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_TYPE_IRQ ; 
 int /*<<< orphan*/  AE_OK ; 

__attribute__((used)) static acpi_status vmbus_walk_resources(struct acpi_resource *res, void *irq)
{

	if (res->type == ACPI_RESOURCE_TYPE_IRQ) {
		struct acpi_resource_irq *irqp;
		irqp = &res->data.irq;

		*((unsigned int *)irq) = irqp->interrupts[0];
	}

	return AE_OK;
}