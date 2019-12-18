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
typedef  int u8 ;
typedef  int u32 ;
struct acpi_pci_id {int bus; int /*<<< orphan*/  function; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_object_type ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_LODWORD (unsigned long long) ; 
 int /*<<< orphan*/  ACPI_LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  METHOD_NAME__ADR ; 
 int /*<<< orphan*/  acpi_evaluate_integer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_parent (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_get_type (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_os_read_pci_configuration (struct acpi_pci_id*,int,int*,int) ; 

__attribute__((used)) static void acpi_os_derive_pci_id_2(acpi_handle rhandle,	/* upper bound  */
				    acpi_handle chandle,	/* current node */
				    struct acpi_pci_id **id,
				    int *is_bridge, u8 * bus_number)
{
	acpi_handle handle;
	struct acpi_pci_id *pci_id = *id;
	acpi_status status;
	unsigned long long temp;
	acpi_object_type type;

	acpi_get_parent(chandle, &handle);
	if (handle != rhandle) {
		acpi_os_derive_pci_id_2(rhandle, handle, &pci_id, is_bridge,
					bus_number);

		status = acpi_get_type(handle, &type);
		if ((ACPI_FAILURE(status)) || (type != ACPI_TYPE_DEVICE))
			return;

		status = acpi_evaluate_integer(handle, METHOD_NAME__ADR, NULL,
					  &temp);
		if (ACPI_SUCCESS(status)) {
			u32 val;
			pci_id->device = ACPI_HIWORD(ACPI_LODWORD(temp));
			pci_id->function = ACPI_LOWORD(ACPI_LODWORD(temp));

			if (*is_bridge)
				pci_id->bus = *bus_number;

			/* any nicer way to get bus number of bridge ? */
			status =
			    acpi_os_read_pci_configuration(pci_id, 0x0e, &val,
							   8);
			if (ACPI_SUCCESS(status)
			    && ((val & 0x7f) == 1 || (val & 0x7f) == 2)) {
				status =
				    acpi_os_read_pci_configuration(pci_id, 0x18,
								   &val, 8);
				if (!ACPI_SUCCESS(status)) {
					/* Certainly broken...  FIX ME */
					return;
				}
				*is_bridge = 1;
				pci_id->bus = val;
				status =
				    acpi_os_read_pci_configuration(pci_id, 0x19,
								   &val, 8);
				if (ACPI_SUCCESS(status)) {
					*bus_number = val;
				}
			} else
				*is_bridge = 0;
		}
	}
}