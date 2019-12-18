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
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  void* acpi_handle ;
struct TYPE_3__ {void* handle; } ;
struct TYPE_4__ {TYPE_1__ atpx; void* dhandle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 void* DEVICE_ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_handle (void*,char*,void**) ; 
 TYPE_2__ radeon_atpx_priv ; 

__attribute__((used)) static bool radeon_atpx_pci_probe_handle(struct pci_dev *pdev)
{
	acpi_handle dhandle, atpx_handle;
	acpi_status status;

	dhandle = DEVICE_ACPI_HANDLE(&pdev->dev);
	if (!dhandle)
		return false;

	status = acpi_get_handle(dhandle, "ATPX", &atpx_handle);
	if (ACPI_FAILURE(status))
		return false;

	radeon_atpx_priv.dhandle = dhandle;
	radeon_atpx_priv.atpx.handle = atpx_handle;
	return true;
}