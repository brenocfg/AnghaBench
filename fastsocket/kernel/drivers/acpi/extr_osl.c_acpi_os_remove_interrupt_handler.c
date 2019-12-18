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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_osd_handler ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_irq ; 
 int /*<<< orphan*/ * acpi_irq_handler ; 
 scalar_t__ acpi_irq_irq ; 
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ ) ; 

acpi_status acpi_os_remove_interrupt_handler(u32 irq, acpi_osd_handler handler)
{
	if (irq) {
		free_irq(irq, acpi_irq);
		acpi_irq_handler = NULL;
		acpi_irq_irq = 0;
	}

	return AE_OK;
}