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
struct TYPE_4__ {int /*<<< orphan*/  possible_count; } ;
struct acpi_pci_link {TYPE_2__ irq; TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_NAME__PRS ; 
 int /*<<< orphan*/  acpi_pci_link_check_possible ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_pci_link*) ; 

__attribute__((used)) static int acpi_pci_link_get_possible(struct acpi_pci_link *link)
{
	acpi_status status;

	status = acpi_walk_resources(link->device->handle, METHOD_NAME__PRS,
				     acpi_pci_link_check_possible, link);
	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Evaluating _PRS"));
		return -ENODEV;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Found %d possible IRQs\n",
			  link->irq.possible_count));

	return 0;
}