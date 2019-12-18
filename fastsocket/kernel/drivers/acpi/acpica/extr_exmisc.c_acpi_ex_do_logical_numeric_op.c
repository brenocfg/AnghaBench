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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_LAND_OP 129 
#define  AML_LOR_OP 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ex_do_logical_numeric_op ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_do_logical_numeric_op(u16 opcode,
			      acpi_integer integer0,
			      acpi_integer integer1, u8 * logical_result)
{
	acpi_status status = AE_OK;
	u8 local_result = FALSE;

	ACPI_FUNCTION_TRACE(ex_do_logical_numeric_op);

	switch (opcode) {
	case AML_LAND_OP:	/* LAnd (Integer0, Integer1) */

		if (integer0 && integer1) {
			local_result = TRUE;
		}
		break;

	case AML_LOR_OP:	/* LOr (Integer0, Integer1) */

		if (integer0 || integer1) {
			local_result = TRUE;
		}
		break;

	default:
		status = AE_AML_INTERNAL;
		break;
	}

	/* Return the logical result and status */

	*logical_result = local_result;
	return_ACPI_STATUS(status);
}