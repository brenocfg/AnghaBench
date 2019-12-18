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
struct TYPE_4__ {int power; } ;
struct TYPE_5__ {unsigned int count; TYPE_3__* states; } ;
struct acpi_processor {TYPE_1__ flags; TYPE_2__ power; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ valid; } ;

/* Variables and functions */
 unsigned int ACPI_PROCESSOR_MAX_POWER ; 
 scalar_t__ ACPI_STATE_C2 ; 
 int ENODEV ; 
 int acpi_processor_get_power_info_cst (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_processor_get_power_info_default (struct acpi_processor*) ; 
 int acpi_processor_get_power_info_fadt (struct acpi_processor*) ; 
 unsigned int acpi_processor_power_verify (struct acpi_processor*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int acpi_processor_get_power_info(struct acpi_processor *pr)
{
	unsigned int i;
	int result;


	/* NOTE: the idle thread may not be running while calling
	 * this function */

	/* Zero initialize all the C-states info. */
	memset(pr->power.states, 0, sizeof(pr->power.states));

	result = acpi_processor_get_power_info_cst(pr);
	if (result == -ENODEV)
		result = acpi_processor_get_power_info_fadt(pr);

	if (result)
		return result;

	acpi_processor_get_power_info_default(pr);

	pr->power.count = acpi_processor_power_verify(pr);

	/*
	 * if one state of type C2 or C3 is available, mark this
	 * CPU as being "idle manageable"
	 */
	for (i = 1; i < ACPI_PROCESSOR_MAX_POWER; i++) {
		if (pr->power.states[i].valid) {
			pr->power.count = i;
			if (pr->power.states[i].type >= ACPI_STATE_C2)
				pr->flags.power = 1;
		}
	}

	return 0;
}