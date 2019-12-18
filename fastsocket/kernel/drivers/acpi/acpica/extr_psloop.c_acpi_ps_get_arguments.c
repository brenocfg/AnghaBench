#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* length; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int aml_opcode; TYPE_2__* parent; void* aml_offset; } ;
union acpi_parse_object {TYPE_4__ named; TYPE_3__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct TYPE_16__ {int /*<<< orphan*/ * pkg_end; int /*<<< orphan*/ * aml; int /*<<< orphan*/  aml_start; } ;
struct acpi_walk_state {int parse_flags; TYPE_7__ parser_state; TYPE_6__* control_state; int /*<<< orphan*/  arg_count; int /*<<< orphan*/  pass_number; int /*<<< orphan*/  owner_id; int /*<<< orphan*/  arg_types; void* aml_offset; } ;
struct acpi_table_header {int dummy; } ;
struct acpi_opcode_info {int /*<<< orphan*/  class; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_14__ {int /*<<< orphan*/ * package_end; } ;
struct TYPE_15__ {TYPE_5__ control; } ;
struct TYPE_10__ {int /*<<< orphan*/  aml_opcode; } ;
struct TYPE_11__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS2 ; 
 int ACPI_PARSE_DISASSEMBLE ; 
 int /*<<< orphan*/  ACPI_PTR_DIFF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_BUFFER_OP 140 
#define  AML_BYTE_OP 139 
 int /*<<< orphan*/  AML_CLASS_EXECUTE ; 
#define  AML_DWORD_OP 138 
#define  AML_ELSE_OP 137 
#define  AML_IF_OP 136 
#define  AML_INT_NAMEPATH_OP 135 
#define  AML_METHOD_OP 134 
 int /*<<< orphan*/  AML_NAME_OP ; 
#define  AML_PACKAGE_OP 133 
#define  AML_QWORD_OP 132 
 int /*<<< orphan*/  AML_SCOPE_OP ; 
#define  AML_STRING_OP 131 
#define  AML_VAR_PACKAGE_OP 130 
#define  AML_WHILE_OP 129 
#define  AML_WORD_OP 128 
 int /*<<< orphan*/  GET_CURRENT_ARG_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INCREMENT_ARG_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_append_arg (union acpi_parse_object*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_get_next_arg (struct acpi_walk_state*,TYPE_7__*,int /*<<< orphan*/ ,union acpi_parse_object**) ; 
 int /*<<< orphan*/  acpi_ps_get_next_namepath (struct acpi_walk_state*,TYPE_7__*,union acpi_parse_object*,int) ; 
 int /*<<< orphan*/  acpi_ps_get_next_simple_arg (TYPE_7__*,int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 struct acpi_opcode_info* acpi_ps_get_opcode_info (int) ; 
 int /*<<< orphan*/  acpi_ps_link_module_code (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_get_arguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ps_get_arguments(struct acpi_walk_state *walk_state,
		      u8 * aml_op_start, union acpi_parse_object *op)
{
	acpi_status status = AE_OK;
	union acpi_parse_object *arg = NULL;
	const struct acpi_opcode_info *op_info;

	ACPI_FUNCTION_TRACE_PTR(ps_get_arguments, walk_state);

	switch (op->common.aml_opcode) {
	case AML_BYTE_OP:	/* AML_BYTEDATA_ARG */
	case AML_WORD_OP:	/* AML_WORDDATA_ARG */
	case AML_DWORD_OP:	/* AML_DWORDATA_ARG */
	case AML_QWORD_OP:	/* AML_QWORDATA_ARG */
	case AML_STRING_OP:	/* AML_ASCIICHARLIST_ARG */

		/* Fill in constant or string argument directly */

		acpi_ps_get_next_simple_arg(&(walk_state->parser_state),
					    GET_CURRENT_ARG_TYPE(walk_state->
								 arg_types),
					    op);
		break;

	case AML_INT_NAMEPATH_OP:	/* AML_NAMESTRING_ARG */

		status =
		    acpi_ps_get_next_namepath(walk_state,
					      &(walk_state->parser_state), op,
					      1);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		walk_state->arg_types = 0;
		break;

	default:
		/*
		 * Op is not a constant or string, append each argument to the Op
		 */
		while (GET_CURRENT_ARG_TYPE(walk_state->arg_types)
		       && !walk_state->arg_count) {
			walk_state->aml_offset =
			    (u32) ACPI_PTR_DIFF(walk_state->parser_state.aml,
						walk_state->parser_state.
						aml_start);

			status =
			    acpi_ps_get_next_arg(walk_state,
						 &(walk_state->parser_state),
						 GET_CURRENT_ARG_TYPE
						 (walk_state->arg_types), &arg);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}

			if (arg) {
				arg->common.aml_offset = walk_state->aml_offset;
				acpi_ps_append_arg(op, arg);
			}

			INCREMENT_ARG_LIST(walk_state->arg_types);
		}

		/*
		 * Handle executable code at "module-level". This refers to
		 * executable opcodes that appear outside of any control method.
		 */
		if ((walk_state->pass_number <= ACPI_IMODE_LOAD_PASS2) &&
		    ((walk_state->parse_flags & ACPI_PARSE_DISASSEMBLE) == 0)) {
			/*
			 * We want to skip If/Else/While constructs during Pass1 because we
			 * want to actually conditionally execute the code during Pass2.
			 *
			 * Except for disassembly, where we always want to walk the
			 * If/Else/While packages
			 */
			switch (op->common.aml_opcode) {
			case AML_IF_OP:
			case AML_ELSE_OP:
			case AML_WHILE_OP:

				/*
				 * Currently supported module-level opcodes are:
				 * IF/ELSE/WHILE. These appear to be the most common,
				 * and easiest to support since they open an AML
				 * package.
				 */
				if (walk_state->pass_number ==
				    ACPI_IMODE_LOAD_PASS1) {
					acpi_ps_link_module_code(aml_op_start,
								 walk_state->
								 parser_state.
								 pkg_end -
								 aml_op_start,
								 walk_state->
								 owner_id);
				}

				ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
						  "Pass1: Skipping an If/Else/While body\n"));

				/* Skip body of if/else/while in pass 1 */

				walk_state->parser_state.aml =
				    walk_state->parser_state.pkg_end;
				walk_state->arg_count = 0;
				break;

			default:
				/*
				 * Check for an unsupported executable opcode at module
				 * level. We must be in PASS1, the parent must be a SCOPE,
				 * The opcode class must be EXECUTE, and the opcode must
				 * not be an argument to another opcode.
				 */
				if ((walk_state->pass_number ==
				     ACPI_IMODE_LOAD_PASS1)
				    && (op->common.parent->common.aml_opcode ==
					AML_SCOPE_OP)) {
					op_info =
					    acpi_ps_get_opcode_info(op->common.
								    aml_opcode);
					if ((op_info->class ==
					     AML_CLASS_EXECUTE) && (!arg)) {
						ACPI_WARNING((AE_INFO,
							      "Detected an unsupported executable opcode "
							      "at module-level: [0x%.4X] at table offset 0x%.4X",
							      op->common.aml_opcode,
							      (u32)((aml_op_start - walk_state->parser_state.aml_start)
								+ sizeof(struct acpi_table_header))));
					}
				}
				break;
			}
		}

		/* Special processing for certain opcodes */

		switch (op->common.aml_opcode) {
		case AML_METHOD_OP:
			/*
			 * Skip parsing of control method because we don't have enough
			 * info in the first pass to parse it correctly.
			 *
			 * Save the length and address of the body
			 */
			op->named.data = walk_state->parser_state.aml;
			op->named.length = (u32)
			    (walk_state->parser_state.pkg_end -
			     walk_state->parser_state.aml);

			/* Skip body of method */

			walk_state->parser_state.aml =
			    walk_state->parser_state.pkg_end;
			walk_state->arg_count = 0;
			break;

		case AML_BUFFER_OP:
		case AML_PACKAGE_OP:
		case AML_VAR_PACKAGE_OP:

			if ((op->common.parent) &&
			    (op->common.parent->common.aml_opcode ==
			     AML_NAME_OP)
			    && (walk_state->pass_number <=
				ACPI_IMODE_LOAD_PASS2)) {
				/*
				 * Skip parsing of Buffers and Packages because we don't have
				 * enough info in the first pass to parse them correctly.
				 */
				op->named.data = aml_op_start;
				op->named.length = (u32)
				    (walk_state->parser_state.pkg_end -
				     aml_op_start);

				/* Skip body */

				walk_state->parser_state.aml =
				    walk_state->parser_state.pkg_end;
				walk_state->arg_count = 0;
			}
			break;

		case AML_WHILE_OP:

			if (walk_state->control_state) {
				walk_state->control_state->control.package_end =
				    walk_state->parser_state.pkg_end;
			}
			break;

		default:

			/* No action for all other opcodes */
			break;
		}

		break;
	}

	return_ACPI_STATUS(AE_OK);
}