#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int integer; void* size; } ;
struct TYPE_4__ {int aml_offset; TYPE_1__ value; } ;
union acpi_parse_object {TYPE_2__ common; } ;
typedef  int u32 ;
typedef  int u16 ;
struct acpi_parse_state {int /*<<< orphan*/  aml; int /*<<< orphan*/  aml_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GET8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NAME_SIZE ; 
 int /*<<< orphan*/  ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  AML_INT_ACCESSFIELD_OP 130 
#define  AML_INT_NAMEDFIELD_OP 129 
#define  AML_INT_RESERVEDFIELD_OP 128 
 union acpi_parse_object* acpi_ps_alloc_op (int) ; 
 void* acpi_ps_get_next_package_length (struct acpi_parse_state*) ; 
 int /*<<< orphan*/  acpi_ps_set_name (union acpi_parse_object*,int) ; 
 int /*<<< orphan*/  ps_get_next_field ; 
 int /*<<< orphan*/  return_PTR (union acpi_parse_object*) ; 

__attribute__((used)) static union acpi_parse_object *acpi_ps_get_next_field(struct acpi_parse_state
						       *parser_state)
{
	u32 aml_offset = (u32)
	    ACPI_PTR_DIFF(parser_state->aml,
			  parser_state->aml_start);
	union acpi_parse_object *field;
	u16 opcode;
	u32 name;

	ACPI_FUNCTION_TRACE(ps_get_next_field);

	/* Determine field type */

	switch (ACPI_GET8(parser_state->aml)) {
	default:

		opcode = AML_INT_NAMEDFIELD_OP;
		break;

	case 0x00:

		opcode = AML_INT_RESERVEDFIELD_OP;
		parser_state->aml++;
		break;

	case 0x01:

		opcode = AML_INT_ACCESSFIELD_OP;
		parser_state->aml++;
		break;
	}

	/* Allocate a new field op */

	field = acpi_ps_alloc_op(opcode);
	if (!field) {
		return_PTR(NULL);
	}

	field->common.aml_offset = aml_offset;

	/* Decode the field type */

	switch (opcode) {
	case AML_INT_NAMEDFIELD_OP:

		/* Get the 4-character name */

		ACPI_MOVE_32_TO_32(&name, parser_state->aml);
		acpi_ps_set_name(field, name);
		parser_state->aml += ACPI_NAME_SIZE;

		/* Get the length which is encoded as a package length */

		field->common.value.size =
		    acpi_ps_get_next_package_length(parser_state);
		break;

	case AML_INT_RESERVEDFIELD_OP:

		/* Get the length which is encoded as a package length */

		field->common.value.size =
		    acpi_ps_get_next_package_length(parser_state);
		break;

	case AML_INT_ACCESSFIELD_OP:

		/*
		 * Get access_type and access_attrib and merge into the field Op
		 * access_type is first operand, access_attribute is second
		 */
		field->common.value.integer =
		    (((u32) ACPI_GET8(parser_state->aml) << 8));
		parser_state->aml++;
		field->common.value.integer |= ACPI_GET8(parser_state->aml);
		parser_state->aml++;
		break;

	default:

		/* Opcode was set in previous switch */
		break;
	}

	return_PTR(field);
}