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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct acpi_walk_state {union acpi_operand_object* return_desc; scalar_t__ return_used; union acpi_operand_object* implicit_return_obj; int /*<<< orphan*/  results; int /*<<< orphan*/  method_call_op; int /*<<< orphan*/  method_node; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi_ds_do_implicit_return (union acpi_operand_object*,struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_result_push (union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_restart_control_method ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_restart_control_method(struct acpi_walk_state *walk_state,
			       union acpi_operand_object *return_desc)
{
	acpi_status status;
	int same_as_implicit_return;

	ACPI_FUNCTION_TRACE_PTR(ds_restart_control_method, walk_state);

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "****Restart [%4.4s] Op %p ReturnValueFromCallee %p\n",
			  acpi_ut_get_node_name(walk_state->method_node),
			  walk_state->method_call_op, return_desc));

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "    ReturnFromThisMethodUsed?=%X ResStack %p Walk %p\n",
			  walk_state->return_used,
			  walk_state->results, walk_state));

	/* Did the called method return a value? */

	if (return_desc) {

		/* Is the implicit return object the same as the return desc? */

		same_as_implicit_return =
		    (walk_state->implicit_return_obj == return_desc);

		/* Are we actually going to use the return value? */

		if (walk_state->return_used) {

			/* Save the return value from the previous method */

			status = acpi_ds_result_push(return_desc, walk_state);
			if (ACPI_FAILURE(status)) {
				acpi_ut_remove_reference(return_desc);
				return_ACPI_STATUS(status);
			}

			/*
			 * Save as THIS method's return value in case it is returned
			 * immediately to yet another method
			 */
			walk_state->return_desc = return_desc;
		}

		/*
		 * The following code is the optional support for the so-called
		 * "implicit return". Some AML code assumes that the last value of the
		 * method is "implicitly" returned to the caller, in the absence of an
		 * explicit return value.
		 *
		 * Just save the last result of the method as the return value.
		 *
		 * NOTE: this is optional because the ASL language does not actually
		 * support this behavior.
		 */
		else if (!acpi_ds_do_implicit_return
			 (return_desc, walk_state, FALSE)
			 || same_as_implicit_return) {
			/*
			 * Delete the return value if it will not be used by the
			 * calling method or remove one reference if the explicit return
			 * is the same as the implicit return value.
			 */
			acpi_ut_remove_reference(return_desc);
		}
	}

	return_ACPI_STATUS(AE_OK);
}