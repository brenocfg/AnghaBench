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
struct TYPE_2__ {int bit_length; } ;
union acpi_operand_object {TYPE_1__ common_field; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int acpi_integer ;

/* Variables and functions */
 int ACPI_INTEGER_BIT_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static u8
acpi_ex_register_overflow(union acpi_operand_object *obj_desc,
			  acpi_integer value)
{

	if (obj_desc->common_field.bit_length >= ACPI_INTEGER_BIT_SIZE) {
		/*
		 * The field is large enough to hold the maximum integer, so we can
		 * never overflow it.
		 */
		return (FALSE);
	}

	if (value >= ((acpi_integer) 1 << obj_desc->common_field.bit_length)) {
		/*
		 * The Value is larger than the maximum value that can fit into
		 * the register.
		 */
		return (TRUE);
	}

	/* The Value will fit into the field with no truncation */

	return (FALSE);
}