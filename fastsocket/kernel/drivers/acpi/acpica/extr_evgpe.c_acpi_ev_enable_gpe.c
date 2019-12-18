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
typedef  int /*<<< orphan*/  u8 ;
struct acpi_gpe_event_info {int flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GPE_ENABLE ; 
 int /*<<< orphan*/  ACPI_GPE_RUN_ENABLED ; 
 int ACPI_GPE_TYPE_MASK ; 
#define  ACPI_GPE_TYPE_RUNTIME 130 
#define  ACPI_GPE_TYPE_WAKE 129 
#define  ACPI_GPE_TYPE_WAKE_RUN 128 
 int /*<<< orphan*/  ACPI_GPE_WAKE_ENABLED ; 
 int /*<<< orphan*/  ACPI_SET_BIT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_update_gpe_enable_masks (struct acpi_gpe_event_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_hw_clear_gpe (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  acpi_hw_write_gpe_enable_reg (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  ev_enable_gpe ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_enable_gpe(struct acpi_gpe_event_info *gpe_event_info,
		   u8 write_to_hardware)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_enable_gpe);

	/* Make sure HW enable masks are updated */

	status =
	    acpi_ev_update_gpe_enable_masks(gpe_event_info, ACPI_GPE_ENABLE);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Mark wake-enabled or HW enable, or both */

	switch (gpe_event_info->flags & ACPI_GPE_TYPE_MASK) {
	case ACPI_GPE_TYPE_WAKE:

		ACPI_SET_BIT(gpe_event_info->flags, ACPI_GPE_WAKE_ENABLED);
		break;

	case ACPI_GPE_TYPE_WAKE_RUN:

		ACPI_SET_BIT(gpe_event_info->flags, ACPI_GPE_WAKE_ENABLED);

		/*lint -fallthrough */

	case ACPI_GPE_TYPE_RUNTIME:

		ACPI_SET_BIT(gpe_event_info->flags, ACPI_GPE_RUN_ENABLED);

		if (write_to_hardware) {

			/* Clear the GPE (of stale events), then enable it */

			status = acpi_hw_clear_gpe(gpe_event_info);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}

			/* Enable the requested runtime GPE */

			status = acpi_hw_write_gpe_enable_reg(gpe_event_info);
		}
		break;

	default:
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	return_ACPI_STATUS(AE_OK);
}