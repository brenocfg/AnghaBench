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
struct acpi_gpe_xrupt_info {scalar_t__ interrupt_number; TYPE_1__* previous; TYPE_2__* next; int /*<<< orphan*/ * gpe_block_list_head; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;
struct TYPE_6__ {scalar_t__ sci_interrupt; } ;
struct TYPE_5__ {TYPE_1__* previous; } ;
struct TYPE_4__ {TYPE_2__* next; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_gpe_xrupt_info*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_gpe_xrupt_handler ; 
 TYPE_3__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_gbl_gpe_lock ; 
 TYPE_2__* acpi_gbl_gpe_xrupt_list_head ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_remove_interrupt_handler (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_delete_gpe_xrupt ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ev_delete_gpe_xrupt(struct acpi_gpe_xrupt_info *gpe_xrupt)
{
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_delete_gpe_xrupt);

	/* We never want to remove the SCI interrupt handler */

	if (gpe_xrupt->interrupt_number == acpi_gbl_FADT.sci_interrupt) {
		gpe_xrupt->gpe_block_list_head = NULL;
		return_ACPI_STATUS(AE_OK);
	}

	/* Disable this interrupt */

	status =
	    acpi_os_remove_interrupt_handler(gpe_xrupt->interrupt_number,
					     acpi_ev_gpe_xrupt_handler);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Unlink the interrupt block with lock */

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	if (gpe_xrupt->previous) {
		gpe_xrupt->previous->next = gpe_xrupt->next;
	} else {
		/* No previous, update list head */

		acpi_gbl_gpe_xrupt_list_head = gpe_xrupt->next;
	}

	if (gpe_xrupt->next) {
		gpe_xrupt->next->previous = gpe_xrupt->previous;
	}
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	/* Free the block */

	ACPI_FREE(gpe_xrupt);
	return_ACPI_STATUS(AE_OK);
}