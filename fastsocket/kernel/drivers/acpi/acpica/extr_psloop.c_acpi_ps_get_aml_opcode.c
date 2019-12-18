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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  aml; int /*<<< orphan*/  aml_start; } ;
struct acpi_walk_state {TYPE_2__* op_info; int /*<<< orphan*/  arg_types; int /*<<< orphan*/  opcode; TYPE_1__ parser_state; scalar_t__ aml_offset; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int class; int /*<<< orphan*/  parse_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DUMP_BUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 scalar_t__ ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_PARSE_CONTINUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_CLASS_ASCII 130 
#define  AML_CLASS_PREFIX 129 
#define  AML_CLASS_UNKNOWN 128 
 int /*<<< orphan*/  AML_INT_NAMEPATH_OP ; 
 int /*<<< orphan*/  ARGP_NAMESTRING ; 
 TYPE_2__* acpi_ps_get_opcode_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_peek_opcode (TYPE_1__*) ; 
 int /*<<< orphan*/  ps_get_aml_opcode ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status acpi_ps_get_aml_opcode(struct acpi_walk_state *walk_state)
{

	ACPI_FUNCTION_TRACE_PTR(ps_get_aml_opcode, walk_state);

	walk_state->aml_offset =
	    (u32) ACPI_PTR_DIFF(walk_state->parser_state.aml,
				walk_state->parser_state.aml_start);
	walk_state->opcode = acpi_ps_peek_opcode(&(walk_state->parser_state));

	/*
	 * First cut to determine what we have found:
	 * 1) A valid AML opcode
	 * 2) A name string
	 * 3) An unknown/invalid opcode
	 */
	walk_state->op_info = acpi_ps_get_opcode_info(walk_state->opcode);

	switch (walk_state->op_info->class) {
	case AML_CLASS_ASCII:
	case AML_CLASS_PREFIX:
		/*
		 * Starts with a valid prefix or ASCII char, this is a name
		 * string. Convert the bare name string to a namepath.
		 */
		walk_state->opcode = AML_INT_NAMEPATH_OP;
		walk_state->arg_types = ARGP_NAMESTRING;
		break;

	case AML_CLASS_UNKNOWN:

		/* The opcode is unrecognized. Just skip unknown opcodes */

		ACPI_ERROR((AE_INFO,
			    "Found unknown opcode %X at AML address %p offset %X, ignoring",
			    walk_state->opcode, walk_state->parser_state.aml,
			    walk_state->aml_offset));

		ACPI_DUMP_BUFFER(walk_state->parser_state.aml, 128);

		/* Assume one-byte bad opcode */

		walk_state->parser_state.aml++;
		return_ACPI_STATUS(AE_CTRL_PARSE_CONTINUE);

	default:

		/* Found opcode info, this is a normal opcode */

		walk_state->parser_state.aml +=
		    acpi_ps_get_opcode_size(walk_state->opcode);
		walk_state->arg_types = walk_state->op_info->parse_args;
		break;
	}

	return_ACPI_STATUS(AE_OK);
}