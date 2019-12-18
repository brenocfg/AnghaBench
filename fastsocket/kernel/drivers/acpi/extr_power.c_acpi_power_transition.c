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
struct acpi_handle_list {int count; int /*<<< orphan*/ * handles; } ;
struct TYPE_4__ {int state; TYPE_1__* states; } ;
struct acpi_device {TYPE_2__ power; } ;
struct TYPE_3__ {struct acpi_handle_list resources; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3 ; 
 int ACPI_STATE_UNKNOWN ; 
 int EINVAL ; 
 int ENODEV ; 
 int acpi_power_off_device (int /*<<< orphan*/ ,struct acpi_device*) ; 
 int acpi_power_on (int /*<<< orphan*/ ,struct acpi_device*) ; 

int acpi_power_transition(struct acpi_device *device, int state)
{
	int result = 0;
	struct acpi_handle_list *cl = NULL;	/* Current Resources */
	struct acpi_handle_list *tl = NULL;	/* Target Resources */
	int i = 0;


	if (!device || (state < ACPI_STATE_D0) || (state > ACPI_STATE_D3))
		return -EINVAL;

	if ((device->power.state < ACPI_STATE_D0)
	    || (device->power.state > ACPI_STATE_D3))
		return -ENODEV;

	cl = &device->power.states[device->power.state].resources;
	tl = &device->power.states[state].resources;

	/* TBD: Resources must be ordered. */

	/*
	 * First we reference all power resources required in the target list
	 * (e.g. so the device doesn't lose power while transitioning).
	 */
	for (i = 0; i < tl->count; i++) {
		result = acpi_power_on(tl->handles[i], device);
		if (result)
			goto end;
	}

	if (device->power.state == state) {
		goto end;
	}

	/*
	 * Then we dereference all power resources used in the current list.
	 */
	for (i = 0; i < cl->count; i++) {
		result = acpi_power_off_device(cl->handles[i], device);
		if (result)
			goto end;
	}

     end:
	if (result)
		device->power.state = ACPI_STATE_UNKNOWN;
	else {
	/* We shouldn't change the state till all above operations succeed */
		device->power.state = state;
	}

	return result;
}