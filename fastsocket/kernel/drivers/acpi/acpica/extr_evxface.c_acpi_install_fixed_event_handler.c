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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ * acpi_event_handler ;
struct TYPE_2__ {int /*<<< orphan*/ * context; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 size_t ACPI_EVENT_MAX ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (size_t,int /*<<< orphan*/ *,void*)) ; 
 int /*<<< orphan*/  ACPI_MTX_EVENTS ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_clear_event (size_t) ; 
 int /*<<< orphan*/  acpi_enable_event (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* acpi_gbl_fixed_event_handlers ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_install_fixed_event_handler(u32 event,
				 acpi_event_handler handler, void *context)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_fixed_event_handler);

	/* Parameter validation */

	if (event > ACPI_EVENT_MAX) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Don't allow two handlers. */

	if (NULL != acpi_gbl_fixed_event_handlers[event].handler) {
		status = AE_ALREADY_EXISTS;
		goto cleanup;
	}

	/* Install the handler before enabling the event */

	acpi_gbl_fixed_event_handlers[event].handler = handler;
	acpi_gbl_fixed_event_handlers[event].context = context;

	status = acpi_clear_event(event);
	if (ACPI_SUCCESS(status))
		status = acpi_enable_event(event, 0);
	if (ACPI_FAILURE(status)) {
		ACPI_WARNING((AE_INFO, "Could not enable fixed event %X",
			      event));

		/* Remove the handler */

		acpi_gbl_fixed_event_handlers[event].handler = NULL;
		acpi_gbl_fixed_event_handlers[event].context = NULL;
	} else {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Enabled fixed event %X, Handler=%p\n", event,
				  handler));
	}

      cleanup:
	(void)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	return_ACPI_STATUS(status);
}