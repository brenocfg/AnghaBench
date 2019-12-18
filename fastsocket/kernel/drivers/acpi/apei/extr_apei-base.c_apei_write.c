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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_generic_address {int space_id; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
#define  ACPI_ADR_SPACE_SYSTEM_IO 129 
#define  ACPI_ADR_SPACE_SYSTEM_MEMORY 128 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_os_write_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_write_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int apei_check_gar (struct acpi_generic_address*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int apei_write(u64 val, struct acpi_generic_address *reg)
{
	int rc;
	u32 access_bit_width;
	u64 address;
	acpi_status status;

	rc = apei_check_gar(reg, &address, &access_bit_width);
	if (rc)
		return rc;

	switch (reg->space_id) {
	case ACPI_ADR_SPACE_SYSTEM_MEMORY:
		status = acpi_os_write_memory((acpi_physical_address) address,
						val, access_bit_width);
		if (ACPI_FAILURE(status))
			return -EIO;
		break;
	case ACPI_ADR_SPACE_SYSTEM_IO:
		status = acpi_os_write_port(address, val, access_bit_width);
		if (ACPI_FAILURE(status))
			return -EIO;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}