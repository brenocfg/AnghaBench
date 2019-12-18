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
 int NOUVEAU_DSM_HAS_MUX ; 
 int NOUVEAU_DSM_HAS_OPT ; 
 int /*<<< orphan*/  NOUVEAU_DSM_OPTIMUS_FN ; 
 int /*<<< orphan*/  NOUVEAU_DSM_POWER ; 
 int /*<<< orphan*/  acpi_get_handle (scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  nouveau_dsm ; 
 TYPE_1__ nouveau_dsm_priv ; 
 int /*<<< orphan*/  nouveau_optimus_dsm ; 
 scalar_t__ nouveau_test_dsm (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nouveau_dsm_pci_probe(struct pci_dev *pdev)
{
	acpi_handle dhandle, nvidia_handle;
	acpi_status status;
	int retval = 0;

	dhandle = DEVICE_ACPI_HANDLE(&pdev->dev);
	if (!dhandle)
		return false;

	status = acpi_get_handle(dhandle, "_DSM", &nvidia_handle);
	if (ACPI_FAILURE(status)) {
		return false;
	}

	if (nouveau_test_dsm(dhandle, nouveau_dsm, NOUVEAU_DSM_POWER))
		retval |= NOUVEAU_DSM_HAS_MUX;

	if (nouveau_test_dsm(dhandle, nouveau_optimus_dsm,
		NOUVEAU_DSM_OPTIMUS_FN))
		retval |= NOUVEAU_DSM_HAS_OPT;

	if (retval)
		nouveau_dsm_priv.dhandle = dhandle;

	return retval;
}