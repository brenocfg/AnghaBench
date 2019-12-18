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
typedef  int u16 ;
typedef  int acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
#define  AML_ADD_OP 137 
#define  AML_BIT_AND_OP 136 
#define  AML_BIT_NAND_OP 135 
#define  AML_BIT_NOR_OP 134 
#define  AML_BIT_OR_OP 133 
#define  AML_BIT_XOR_OP 132 
#define  AML_MULTIPLY_OP 131 
#define  AML_SHIFT_LEFT_OP 130 
#define  AML_SHIFT_RIGHT_OP 129 
#define  AML_SUBTRACT_OP 128 
 int acpi_gbl_integer_bit_width ; 

acpi_integer
acpi_ex_do_math_op(u16 opcode, acpi_integer integer0, acpi_integer integer1)
{

	ACPI_FUNCTION_ENTRY();

	switch (opcode) {
	case AML_ADD_OP:	/* Add (Integer0, Integer1, Result) */

		return (integer0 + integer1);

	case AML_BIT_AND_OP:	/* And (Integer0, Integer1, Result) */

		return (integer0 & integer1);

	case AML_BIT_NAND_OP:	/* NAnd (Integer0, Integer1, Result) */

		return (~(integer0 & integer1));

	case AML_BIT_OR_OP:	/* Or (Integer0, Integer1, Result) */

		return (integer0 | integer1);

	case AML_BIT_NOR_OP:	/* NOr (Integer0, Integer1, Result) */

		return (~(integer0 | integer1));

	case AML_BIT_XOR_OP:	/* XOr (Integer0, Integer1, Result) */

		return (integer0 ^ integer1);

	case AML_MULTIPLY_OP:	/* Multiply (Integer0, Integer1, Result) */

		return (integer0 * integer1);

	case AML_SHIFT_LEFT_OP:	/* shift_left (Operand, shift_count, Result) */

		/*
		 * We need to check if the shiftcount is larger than the integer bit
		 * width since the behavior of this is not well-defined in the C language.
		 */
		if (integer1 >= acpi_gbl_integer_bit_width) {
			return (0);
		}
		return (integer0 << integer1);

	case AML_SHIFT_RIGHT_OP:	/* shift_right (Operand, shift_count, Result) */

		/*
		 * We need to check if the shiftcount is larger than the integer bit
		 * width since the behavior of this is not well-defined in the C language.
		 */
		if (integer1 >= acpi_gbl_integer_bit_width) {
			return (0);
		}
		return (integer0 >> integer1);

	case AML_SUBTRACT_OP:	/* Subtract (Integer0, Integer1, Result) */

		return (integer0 - integer1);

	default:

		return (0);
	}
}