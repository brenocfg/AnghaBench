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
struct acpi_processor_cx {int type; int valid; } ;
struct TYPE_2__ {struct acpi_processor_cx* states; int /*<<< orphan*/  timer_broadcast_on_state; } ;
struct acpi_processor {int /*<<< orphan*/  id; TYPE_1__ power; } ;

/* Variables and functions */
 unsigned int ACPI_PROCESSOR_MAX_POWER ; 
#define  ACPI_STATE_C1 130 
#define  ACPI_STATE_C2 129 
#define  ACPI_STATE_C3 128 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  acpi_processor_power_verify_c2 (struct acpi_processor_cx*) ; 
 int /*<<< orphan*/  acpi_processor_power_verify_c3 (struct acpi_processor*,struct acpi_processor_cx*) ; 
 int /*<<< orphan*/  lapic_timer_check_state (unsigned int,struct acpi_processor*,struct acpi_processor_cx*) ; 
 int /*<<< orphan*/  lapic_timer_propagate_broadcast ; 
 unsigned int max_cstate ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_processor*,int) ; 
 int /*<<< orphan*/  tsc_check_state (int) ; 

__attribute__((used)) static int acpi_processor_power_verify(struct acpi_processor *pr)
{
	unsigned int i;
	unsigned int working = 0;

	pr->power.timer_broadcast_on_state = INT_MAX;

	for (i = 1; i < ACPI_PROCESSOR_MAX_POWER && i <= max_cstate; i++) {
		struct acpi_processor_cx *cx = &pr->power.states[i];

		switch (cx->type) {
		case ACPI_STATE_C1:
			cx->valid = 1;
			break;

		case ACPI_STATE_C2:
			acpi_processor_power_verify_c2(cx);
			break;

		case ACPI_STATE_C3:
			acpi_processor_power_verify_c3(pr, cx);
			break;
		}
		if (!cx->valid)
			continue;

		lapic_timer_check_state(i, pr, cx);
		tsc_check_state(cx->type);
		working++;
	}

	smp_call_function_single(pr->id, lapic_timer_propagate_broadcast,
				 pr, 1);

	return (working);
}