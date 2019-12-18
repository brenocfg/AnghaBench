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
struct acpi_handle_list {size_t count; int /*<<< orphan*/ * handles; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int ACPI_POWER_RESOURCE_STATE_ON ; 
 int EINVAL ; 
 int acpi_power_get_state (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int acpi_power_get_list_state(struct acpi_handle_list *list, int *state)
{
	int result = 0, state1;
	u32 i = 0;


	if (!list || !state)
		return -EINVAL;

	/* The state of the list is 'on' IFF all resources are 'on'. */
	/* */

	for (i = 0; i < list->count; i++) {
		/*
		 * The state of the power resource can be obtained by
		 * using the ACPI handle. In such case it is unnecessary to
		 * get the Power resource first and then get its state again.
		 */
		result = acpi_power_get_state(list->handles[i], &state1);
		if (result)
			return result;

		*state = state1;

		if (*state != ACPI_POWER_RESOURCE_STATE_ON)
			break;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Resource list is %s\n",
			  *state ? "on" : "off"));

	return result;
}