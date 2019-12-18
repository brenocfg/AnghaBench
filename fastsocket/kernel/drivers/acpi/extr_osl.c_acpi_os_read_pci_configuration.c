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
typedef  int u32 ;
struct acpi_pci_id {int /*<<< orphan*/  function; int /*<<< orphan*/  device; int /*<<< orphan*/  bus; int /*<<< orphan*/  segment; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int raw_pci_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 

acpi_status
acpi_os_read_pci_configuration(struct acpi_pci_id * pci_id, u32 reg,
			       u32 *value, u32 width)
{
	int result, size;

	if (!value)
		return AE_BAD_PARAMETER;

	switch (width) {
	case 8:
		size = 1;
		break;
	case 16:
		size = 2;
		break;
	case 32:
		size = 4;
		break;
	default:
		return AE_ERROR;
	}

	result = raw_pci_read(pci_id->segment, pci_id->bus,
				PCI_DEVFN(pci_id->device, pci_id->function),
				reg, size, value);

	return (result ? AE_ERROR : AE_OK);
}