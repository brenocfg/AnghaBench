#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; } ;
struct TYPE_6__ {int /*<<< orphan*/  aml_opcode; TYPE_1__ value; union acpi_parse_object* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
union acpi_parse_object {TYPE_3__ common; TYPE_2__ named; } ;
typedef  int u32 ;
struct acpi_walk_state {int arg_count; int /*<<< orphan*/  opcode; } ;
struct acpi_parse_state {int /*<<< orphan*/  pkg_end; int /*<<< orphan*/  aml; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_parse_state*) ; 
 int /*<<< orphan*/  ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ACPI_VAR_ARGS ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AML_BYTE_OP ; 
 int /*<<< orphan*/  AML_INT_BYTELIST_OP ; 
 int /*<<< orphan*/  AML_INT_METHODCALL_OP ; 
 int /*<<< orphan*/  AML_INT_NAMEPATH_OP ; 
 int /*<<< orphan*/  AML_UNLOAD_OP ; 
#define  ARGP_BYTEDATA 144 
#define  ARGP_BYTELIST 143 
#define  ARGP_CHARLIST 142 
#define  ARGP_DATAOBJ 141 
#define  ARGP_DATAOBJLIST 140 
#define  ARGP_DWORDDATA 139 
#define  ARGP_FIELDLIST 138 
#define  ARGP_NAME 137 
#define  ARGP_NAMESTRING 136 
#define  ARGP_OBJLIST 135 
#define  ARGP_PKGLENGTH 134 
#define  ARGP_SIMPLENAME 133 
#define  ARGP_SUPERNAME 132 
#define  ARGP_TARGET 131 
#define  ARGP_TERMARG 130 
#define  ARGP_TERMLIST 129 
#define  ARGP_WORDDATA 128 
 union acpi_parse_object* acpi_ps_alloc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_free_op (union acpi_parse_object*) ; 
 union acpi_parse_object* acpi_ps_get_next_field (struct acpi_parse_state*) ; 
 int /*<<< orphan*/  acpi_ps_get_next_namepath (struct acpi_walk_state*,struct acpi_parse_state*,union acpi_parse_object*,int) ; 
 int /*<<< orphan*/  acpi_ps_get_next_package_end (struct acpi_parse_state*) ; 
 int /*<<< orphan*/  acpi_ps_get_next_simple_arg (struct acpi_parse_state*,int,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_is_leading_char (int) ; 
 int /*<<< orphan*/  acpi_ps_is_prefix_char (int) ; 
 int acpi_ps_peek_opcode (struct acpi_parse_state*) ; 
 int /*<<< orphan*/  ps_get_next_arg ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ps_get_next_arg(struct acpi_walk_state *walk_state,
		     struct acpi_parse_state *parser_state,
		     u32 arg_type, union acpi_parse_object **return_arg)
{
	union acpi_parse_object *arg = NULL;
	union acpi_parse_object *prev = NULL;
	union acpi_parse_object *field;
	u32 subop;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ps_get_next_arg, parser_state);

	switch (arg_type) {
	case ARGP_BYTEDATA:
	case ARGP_WORDDATA:
	case ARGP_DWORDDATA:
	case ARGP_CHARLIST:
	case ARGP_NAME:
	case ARGP_NAMESTRING:

		/* Constants, strings, and namestrings are all the same size */

		arg = acpi_ps_alloc_op(AML_BYTE_OP);
		if (!arg) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}
		acpi_ps_get_next_simple_arg(parser_state, arg_type, arg);
		break;

	case ARGP_PKGLENGTH:

		/* Package length, nothing returned */

		parser_state->pkg_end =
		    acpi_ps_get_next_package_end(parser_state);
		break;

	case ARGP_FIELDLIST:

		if (parser_state->aml < parser_state->pkg_end) {

			/* Non-empty list */

			while (parser_state->aml < parser_state->pkg_end) {
				field = acpi_ps_get_next_field(parser_state);
				if (!field) {
					return_ACPI_STATUS(AE_NO_MEMORY);
				}

				if (prev) {
					prev->common.next = field;
				} else {
					arg = field;
				}
				prev = field;
			}

			/* Skip to End of byte data */

			parser_state->aml = parser_state->pkg_end;
		}
		break;

	case ARGP_BYTELIST:

		if (parser_state->aml < parser_state->pkg_end) {

			/* Non-empty list */

			arg = acpi_ps_alloc_op(AML_INT_BYTELIST_OP);
			if (!arg) {
				return_ACPI_STATUS(AE_NO_MEMORY);
			}

			/* Fill in bytelist data */

			arg->common.value.size = (u32)
			    ACPI_PTR_DIFF(parser_state->pkg_end,
					  parser_state->aml);
			arg->named.data = parser_state->aml;

			/* Skip to End of byte data */

			parser_state->aml = parser_state->pkg_end;
		}
		break;

	case ARGP_TARGET:
	case ARGP_SUPERNAME:
	case ARGP_SIMPLENAME:

		subop = acpi_ps_peek_opcode(parser_state);
		if (subop == 0 ||
		    acpi_ps_is_leading_char(subop) ||
		    acpi_ps_is_prefix_char(subop)) {

			/* null_name or name_string */

			arg = acpi_ps_alloc_op(AML_INT_NAMEPATH_OP);
			if (!arg) {
				return_ACPI_STATUS(AE_NO_MEMORY);
			}

			/* To support super_name arg of Unload */

			if (walk_state->opcode == AML_UNLOAD_OP) {
				status =
				    acpi_ps_get_next_namepath(walk_state,
							      parser_state, arg,
							      1);

				/*
				 * If the super_name arg of Unload is a method call,
				 * we have restored the AML pointer, just free this Arg
				 */
				if (arg->common.aml_opcode ==
				    AML_INT_METHODCALL_OP) {
					acpi_ps_free_op(arg);
					arg = NULL;
				}
			} else {
				status =
				    acpi_ps_get_next_namepath(walk_state,
							      parser_state, arg,
							      0);
			}
		} else {
			/* Single complex argument, nothing returned */

			walk_state->arg_count = 1;
		}
		break;

	case ARGP_DATAOBJ:
	case ARGP_TERMARG:

		/* Single complex argument, nothing returned */

		walk_state->arg_count = 1;
		break;

	case ARGP_DATAOBJLIST:
	case ARGP_TERMLIST:
	case ARGP_OBJLIST:

		if (parser_state->aml < parser_state->pkg_end) {

			/* Non-empty list of variable arguments, nothing returned */

			walk_state->arg_count = ACPI_VAR_ARGS;
		}
		break;

	default:

		ACPI_ERROR((AE_INFO, "Invalid ArgType: %X", arg_type));
		status = AE_AML_OPERAND_TYPE;
		break;
	}

	*return_arg = arg;
	return_ACPI_STATUS(status);
}