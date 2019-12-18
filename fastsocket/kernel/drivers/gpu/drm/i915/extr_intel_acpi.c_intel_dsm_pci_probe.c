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
typedef  scalar_t__ acpi_handle ;
struct TYPE_2__ {scalar_t__ dhandle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ DEVICE_ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  INTEL_DSM_FN_SUPPORTED_FUNCTIONS ; 
 int /*<<< orphan*/  acpi_get_handle (scalar_t__,char*,scalar_t__*) ; 
 int intel_dsm (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dsm_platform_mux_info () ; 
 TYPE_1__ intel_dsm_priv ; 

__attribute__((used)) static bool intel_dsm_pci_probe(struct pci_dev *pdev)
{
	acpi_handle dhandle, intel_handle;
	acpi_status status;
	int ret;

	dhandle = DEVICE_ACPI_HANDLE(&pdev->dev);
	if (!dhandle)
		return false;

	status = acpi_get_handle(dhandle, "_DSM", &intel_handle);
	if (ACPI_FAILURE(status)) {
		DRM_DEBUG_KMS("no _DSM method for intel device\n");
		return false;
	}

	ret = intel_dsm(dhandle, INTEL_DSM_FN_SUPPORTED_FUNCTIONS, 0);
	if (ret < 0) {
		DRM_DEBUG_KMS("failed to get supported _DSM functions\n");
		return false;
	}

	intel_dsm_priv.dhandle = dhandle;

	intel_dsm_platform_mux_info();
	return true;
}