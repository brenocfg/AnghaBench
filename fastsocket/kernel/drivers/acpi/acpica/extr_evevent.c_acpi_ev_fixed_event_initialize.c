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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int /*<<< orphan*/ * context; int /*<<< orphan*/ * handler; } ;
struct TYPE_3__ {int enable_register_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DISABLE_EVENT ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t ACPI_NUM_FIXED_EVENTS ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__* acpi_gbl_fixed_event_handlers ; 
 TYPE_1__* acpi_gbl_fixed_event_info ; 
 int /*<<< orphan*/  acpi_write_bit_register (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status acpi_ev_fixed_event_initialize(void)
{
	u32 i;
	acpi_status status;

	/*
	 * Initialize the structure that keeps track of fixed event handlers and
	 * enable the fixed events.
	 */
	for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {
		acpi_gbl_fixed_event_handlers[i].handler = NULL;
		acpi_gbl_fixed_event_handlers[i].context = NULL;

		/* Disable the fixed event */

		if (acpi_gbl_fixed_event_info[i].enable_register_id != 0xFF) {
			status =
			    acpi_write_bit_register(acpi_gbl_fixed_event_info
						    [i].enable_register_id,
						    ACPI_DISABLE_EVENT);
			if (ACPI_FAILURE(status)) {
				return (status);
			}
		}
	}

	return (AE_OK);
}