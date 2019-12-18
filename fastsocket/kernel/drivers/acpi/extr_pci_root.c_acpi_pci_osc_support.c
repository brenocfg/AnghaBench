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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_pci_root {TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_pci_query_osc (struct acpi_pci_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osc_lock ; 

__attribute__((used)) static acpi_status acpi_pci_osc_support(struct acpi_pci_root *root, u32 flags)
{
	acpi_status status;
	acpi_handle tmp;

	status = acpi_get_handle(root->device->handle, "_OSC", &tmp);
	if (ACPI_FAILURE(status))
		return status;
	mutex_lock(&osc_lock);
	status = acpi_pci_query_osc(root, flags, NULL);
	mutex_unlock(&osc_lock);
	return status;
}