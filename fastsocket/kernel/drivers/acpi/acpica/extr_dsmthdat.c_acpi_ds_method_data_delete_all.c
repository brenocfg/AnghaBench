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
typedef  size_t u32 ;
struct acpi_walk_state {TYPE_1__* arguments; TYPE_1__* local_variables; } ;
struct TYPE_2__ {scalar_t__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 size_t ACPI_METHOD_NUM_ARGS ; 
 size_t ACPI_METHOD_NUM_LOCALS ; 
 int /*<<< orphan*/  acpi_ns_detach_object (TYPE_1__*) ; 
 int /*<<< orphan*/  ds_method_data_delete_all ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ds_method_data_delete_all(struct acpi_walk_state *walk_state)
{
	u32 index;

	ACPI_FUNCTION_TRACE(ds_method_data_delete_all);

	/* Detach the locals */

	for (index = 0; index < ACPI_METHOD_NUM_LOCALS; index++) {
		if (walk_state->local_variables[index].object) {
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Deleting Local%d=%p\n",
					  index,
					  walk_state->local_variables[index].
					  object));

			/* Detach object (if present) and remove a reference */

			acpi_ns_detach_object(&walk_state->
					      local_variables[index]);
		}
	}

	/* Detach the arguments */

	for (index = 0; index < ACPI_METHOD_NUM_ARGS; index++) {
		if (walk_state->arguments[index].object) {
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Deleting Arg%d=%p\n",
					  index,
					  walk_state->arguments[index].object));

			/* Detach object (if present) and remove a reference */

			acpi_ns_detach_object(&walk_state->arguments[index]);
		}
	}

	return_VOID;
}