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
struct acpi_table_desc {int flags; int /*<<< orphan*/  length; scalar_t__ pointer; int /*<<< orphan*/  signature; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAME (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_FACS ; 
 int ACPI_TABLE_ORIGIN_MAPPED ; 
 int ACPI_TABLE_ORIGIN_MASK ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_os_map_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_verify_checksum (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_verify_table ; 

acpi_status acpi_tb_verify_table(struct acpi_table_desc *table_desc)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(tb_verify_table);

	/* Map the table if necessary */

	if (!table_desc->pointer) {
		if ((table_desc->flags & ACPI_TABLE_ORIGIN_MASK) ==
		    ACPI_TABLE_ORIGIN_MAPPED) {
			table_desc->pointer =
			    acpi_os_map_memory(table_desc->address,
					       table_desc->length);
		}
		if (!table_desc->pointer) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}
	}

	/* FACS is the odd table, has no standard ACPI header and no checksum */

	if (!ACPI_COMPARE_NAME(&table_desc->signature, ACPI_SIG_FACS)) {

		/* Always calculate checksum, ignore bad checksum if requested */

		status =
		    acpi_tb_verify_checksum(table_desc->pointer,
					    table_desc->length);
	}

	return_ACPI_STATUS(status);
}