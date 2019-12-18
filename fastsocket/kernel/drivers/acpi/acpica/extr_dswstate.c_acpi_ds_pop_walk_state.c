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
struct acpi_walk_state {struct acpi_walk_state* next; } ;
struct acpi_thread_state {struct acpi_walk_state* walk_state_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_pop_walk_state ; 
 int /*<<< orphan*/  return_PTR (struct acpi_walk_state*) ; 

struct acpi_walk_state *acpi_ds_pop_walk_state(struct acpi_thread_state *thread)
{
	struct acpi_walk_state *walk_state;

	ACPI_FUNCTION_TRACE(ds_pop_walk_state);

	walk_state = thread->walk_state_list;

	if (walk_state) {

		/* Next walk state becomes the current walk state */

		thread->walk_state_list = walk_state->next;

		/*
		 * Don't clear the NEXT field, this serves as an indicator
		 * that there is a parent WALK STATE
		 * Do Not: walk_state->Next = NULL;
		 */
	}

	return_PTR(walk_state);
}