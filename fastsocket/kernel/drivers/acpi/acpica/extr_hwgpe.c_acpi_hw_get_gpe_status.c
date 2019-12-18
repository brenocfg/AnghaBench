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
typedef  int u8 ;
typedef  int u32 ;
struct acpi_gpe_register_info {int base_gpe_number; int enable_for_run; int enable_for_wake; int /*<<< orphan*/  status_address; } ;
struct acpi_gpe_event_info {int gpe_number; struct acpi_gpe_register_info* register_info; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_event_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVENT_FLAG_ENABLED ; 
 int /*<<< orphan*/  ACPI_EVENT_FLAG_SET ; 
 int /*<<< orphan*/  ACPI_EVENT_FLAG_WAKE_ENABLED ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  acpi_hw_read (int*,int /*<<< orphan*/ *) ; 

acpi_status
acpi_hw_get_gpe_status(struct acpi_gpe_event_info * gpe_event_info,
		       acpi_event_status * event_status)
{
	u32 in_byte;
	u8 register_bit;
	struct acpi_gpe_register_info *gpe_register_info;
	acpi_status status;
	acpi_event_status local_event_status = 0;

	ACPI_FUNCTION_ENTRY();

	if (!event_status) {
		return (AE_BAD_PARAMETER);
	}

	/* Get the info block for the entire GPE register */

	gpe_register_info = gpe_event_info->register_info;

	/* Get the register bitmask for this GPE */

	register_bit = (u8)(1 <<
			    (gpe_event_info->gpe_number -
			     gpe_event_info->register_info->base_gpe_number));

	/* GPE currently enabled? (enabled for runtime?) */

	if (register_bit & gpe_register_info->enable_for_run) {
		local_event_status |= ACPI_EVENT_FLAG_ENABLED;
	}

	/* GPE enabled for wake? */

	if (register_bit & gpe_register_info->enable_for_wake) {
		local_event_status |= ACPI_EVENT_FLAG_WAKE_ENABLED;
	}

	/* GPE currently active (status bit == 1)? */

	status = acpi_hw_read(&in_byte, &gpe_register_info->status_address);
	if (ACPI_FAILURE(status)) {
		goto unlock_and_exit;
	}

	if (register_bit & in_byte) {
		local_event_status |= ACPI_EVENT_FLAG_SET;
	}

	/* Set return value */

	(*event_status) = local_event_status;

      unlock_and_exit:
	return (status);
}