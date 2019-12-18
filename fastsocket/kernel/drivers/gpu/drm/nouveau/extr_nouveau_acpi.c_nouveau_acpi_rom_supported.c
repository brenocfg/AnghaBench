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
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  rom_handle; int /*<<< orphan*/  optimus_detected; int /*<<< orphan*/  dsm_detected; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVICE_ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ nouveau_dsm_priv ; 

bool nouveau_acpi_rom_supported(struct pci_dev *pdev)
{
	acpi_status status;
	acpi_handle dhandle, rom_handle;

	if (!nouveau_dsm_priv.dsm_detected && !nouveau_dsm_priv.optimus_detected)
		return false;

	dhandle = DEVICE_ACPI_HANDLE(&pdev->dev);
	if (!dhandle)
		return false;

	status = acpi_get_handle(dhandle, "_ROM", &rom_handle);
	if (ACPI_FAILURE(status))
		return false;

	nouveau_dsm_priv.rom_handle = rom_handle;
	return true;
}