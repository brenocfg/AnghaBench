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
typedef  size_t u32 ;
struct acpi_walk_state {size_t num_operands; int /*<<< orphan*/ ** operands; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds_clear_operands ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ds_clear_operands(struct acpi_walk_state *walk_state)
{
	u32 i;

	ACPI_FUNCTION_TRACE_PTR(ds_clear_operands, walk_state);

	/* Remove a reference on each operand on the stack */

	for (i = 0; i < walk_state->num_operands; i++) {
		/*
		 * Remove a reference to all operands, including both
		 * "Arguments" and "Targets".
		 */
		acpi_ut_remove_reference(walk_state->operands[i]);
		walk_state->operands[i] = NULL;
	}

	walk_state->num_operands = 0;
	return_VOID;
}