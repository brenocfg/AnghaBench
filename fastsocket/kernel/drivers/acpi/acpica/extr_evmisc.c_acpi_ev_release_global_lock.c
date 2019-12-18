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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {int /*<<< orphan*/  os_mutex; } ;
struct TYPE_4__ {TYPE_1__ mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_GLOBAL_LOCK_RELEASE ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ENABLE_EVENT ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_RELEASE_GLOBAL_LOCK (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_OK ; 
 void* FALSE ; 
 scalar_t__ acpi_ev_global_lock_acquired ; 
 int /*<<< orphan*/ * acpi_ev_global_lock_thread_id ; 
 int /*<<< orphan*/  acpi_gbl_FACS ; 
 void* acpi_gbl_global_lock_acquired ; 
 TYPE_2__* acpi_gbl_global_lock_mutex ; 
 scalar_t__ acpi_gbl_global_lock_present ; 
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_write_bit_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_release_global_lock ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ev_release_global_lock(void)
{
	u8 pending = FALSE;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ev_release_global_lock);

	/* Lock must be already acquired */

	if (!acpi_gbl_global_lock_acquired) {
		ACPI_WARNING((AE_INFO,
			      "Cannot release the ACPI Global Lock, it has not been acquired"));
		return_ACPI_STATUS(AE_NOT_ACQUIRED);
	}

	acpi_ev_global_lock_acquired--;
	if (acpi_ev_global_lock_acquired > 0) {
		return AE_OK;
	}

	if (acpi_gbl_global_lock_present) {

		/* Allow any thread to release the lock */

		ACPI_RELEASE_GLOBAL_LOCK(acpi_gbl_FACS, pending);

		/*
		 * If the pending bit was set, we must write GBL_RLS to the control
		 * register
		 */
		if (pending) {
			status =
			    acpi_write_bit_register
			    (ACPI_BITREG_GLOBAL_LOCK_RELEASE,
			     ACPI_ENABLE_EVENT);
		}

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Released hardware Global Lock\n"));
	}

	acpi_gbl_global_lock_acquired = FALSE;

	/* Release the local GL mutex */
	acpi_ev_global_lock_thread_id = NULL;
	acpi_ev_global_lock_acquired = 0;
	acpi_os_release_mutex(acpi_gbl_global_lock_mutex->mutex.os_mutex);
	return_ACPI_STATUS(status);
}