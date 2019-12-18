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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_integer ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_READ ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_address_space_dispatch (union acpi_operand_object*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*) ; 

__attribute__((used)) static acpi_status
acpi_ex_region_read(union acpi_operand_object *obj_desc, u32 length, u8 *buffer)
{
	acpi_status status;
	acpi_integer value;
	u32 region_offset = 0;
	u32 i;

	/* Bytewise reads */

	for (i = 0; i < length; i++) {
		status = acpi_ev_address_space_dispatch(obj_desc, ACPI_READ,
							region_offset, 8,
							&value);
		if (ACPI_FAILURE(status)) {
			return status;
		}

		*buffer = (u8)value;
		buffer++;
		region_offset++;
	}

	return AE_OK;
}