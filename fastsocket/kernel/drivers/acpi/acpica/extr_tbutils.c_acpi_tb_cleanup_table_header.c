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
struct acpi_table_header {int /*<<< orphan*/  asl_compiler_id; int /*<<< orphan*/  oem_table_id; int /*<<< orphan*/  oem_id; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_MEMCPY (struct acpi_table_header*,struct acpi_table_header*,int) ; 
 int /*<<< orphan*/  ACPI_NAME_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_ID_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_TABLE_ID_SIZE ; 
 int /*<<< orphan*/  acpi_tb_fix_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_tb_cleanup_table_header(struct acpi_table_header *out_header,
			     struct acpi_table_header *header)
{

	ACPI_MEMCPY(out_header, header, sizeof(struct acpi_table_header));

	acpi_tb_fix_string(out_header->signature, ACPI_NAME_SIZE);
	acpi_tb_fix_string(out_header->oem_id, ACPI_OEM_ID_SIZE);
	acpi_tb_fix_string(out_header->oem_table_id, ACPI_OEM_TABLE_ID_SIZE);
	acpi_tb_fix_string(out_header->asl_compiler_id, ACPI_NAME_SIZE);
}