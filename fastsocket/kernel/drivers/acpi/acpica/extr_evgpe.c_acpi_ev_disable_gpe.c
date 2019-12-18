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
struct acpi_gpe_event_info {int flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CLEAR_BIT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GPE_DISABLE ; 
 int /*<<< orphan*/  ACPI_GPE_RUN_ENABLED ; 
 int ACPI_GPE_TYPE_MASK ; 
#define  ACPI_GPE_TYPE_RUNTIME 130 
#define  ACPI_GPE_TYPE_WAKE 129 
#define  ACPI_GPE_TYPE_WAKE_RUN 128 
 int /*<<< orphan*/  ACPI_GPE_WAKE_ENABLED ; 
 int /*<<< orphan*/  acpi_ev_update_gpe_enable_masks (struct acpi_gpe_event_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_hw_low_disable_gpe (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  ev_disable_gpe ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ev_disable_gpe(struct acpi_gpe_event_info *gpe_event_info)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_disable_gpe);

	/* Make sure HW enable masks are updated */

	status =
	    acpi_ev_update_gpe_enable_masks(gpe_event_info, ACPI_GPE_DISABLE);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Clear the appropriate enabled flags for this GPE */

	switch (gpe_event_info->flags & ACPI_GPE_TYPE_MASK) {
	case ACPI_GPE_TYPE_WAKE:
		ACPI_CLEAR_BIT(gpe_event_info->flags, ACPI_GPE_WAKE_ENABLED);
		break;

	case ACPI_GPE_TYPE_WAKE_RUN:
		ACPI_CLEAR_BIT(gpe_event_info->flags, ACPI_GPE_WAKE_ENABLED);

		/* fallthrough */

	case ACPI_GPE_TYPE_RUNTIME:

		/* Disable the requested runtime GPE */

		ACPI_CLEAR_BIT(gpe_event_info->flags, ACPI_GPE_RUN_ENABLED);
		break;

	default:
		break;
	}

	/*
	 * Even if we don't know the GPE type, make sure that we always
	 * disable it. low_disable_gpe will just clear the enable bit for this
	 * GPE and write it. It will not write out the current GPE enable mask,
	 * since this may inadvertently enable GPEs too early, if a rogue GPE has
	 * come in during ACPICA initialization - possibly as a result of AML or
	 * other code that has enabled the GPE.
	 */
	status = acpi_hw_low_disable_gpe(gpe_event_info);
	return_ACPI_STATUS(status);
}