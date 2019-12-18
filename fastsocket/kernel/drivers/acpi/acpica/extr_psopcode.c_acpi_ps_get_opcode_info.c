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
typedef  size_t u8 ;
typedef  int u16 ;
struct acpi_opcode_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int AML_EXTENDED_OPCODE ; 
 size_t MAX_EXTENDED_OPCODE ; 
 size_t _UNK ; 
 struct acpi_opcode_info const* acpi_gbl_aml_op_info ; 
 size_t* acpi_gbl_long_op_index ; 
 size_t* acpi_gbl_short_op_index ; 
 int /*<<< orphan*/  ps_get_opcode_info ; 

const struct acpi_opcode_info *acpi_ps_get_opcode_info(u16 opcode)
{
	ACPI_FUNCTION_NAME(ps_get_opcode_info);

	/*
	 * Detect normal 8-bit opcode or extended 16-bit opcode
	 */
	if (!(opcode & 0xFF00)) {

		/* Simple (8-bit) opcode: 0-255, can't index beyond table  */

		return (&acpi_gbl_aml_op_info
			[acpi_gbl_short_op_index[(u8) opcode]]);
	}

	if (((opcode & 0xFF00) == AML_EXTENDED_OPCODE) &&
	    (((u8) opcode) <= MAX_EXTENDED_OPCODE)) {

		/* Valid extended (16-bit) opcode */

		return (&acpi_gbl_aml_op_info
			[acpi_gbl_long_op_index[(u8) opcode]]);
	}

	/* Unknown AML opcode */

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Unknown AML opcode [%4.4X]\n", opcode));

	return (&acpi_gbl_aml_op_info[_UNK]);
}