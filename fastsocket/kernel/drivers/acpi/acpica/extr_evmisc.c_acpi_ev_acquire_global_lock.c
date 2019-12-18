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
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;
struct TYPE_3__ {int /*<<< orphan*/  os_mutex; } ;
struct TYPE_4__ {TYPE_1__ mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ACQUIRE_GLOBAL_LOCK (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AE_TIME ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  acpi_ev_global_lock_acquired ; 
 void* acpi_ev_global_lock_pending ; 
 int /*<<< orphan*/  acpi_ev_global_lock_pending_lock ; 
 scalar_t__ acpi_ev_global_lock_thread_id ; 
 scalar_t__ acpi_ex_system_wait_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ex_system_wait_semaphore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_FACS ; 
 void* acpi_gbl_global_lock_acquired ; 
 int acpi_gbl_global_lock_handle ; 
 TYPE_2__* acpi_gbl_global_lock_mutex ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_present ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_semaphore ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_os_get_thread_id () ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_acquire_global_lock ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status acpi_ev_acquire_global_lock(u16 timeout)
{
	acpi_cpu_flags flags;
	acpi_status status = AE_OK;
	u8 acquired = FALSE;

	ACPI_FUNCTION_TRACE(ev_acquire_global_lock);

	/*
	 * Only one thread can acquire the GL at a time, the global_lock_mutex
	 * enforces this. This interface releases the interpreter if we must wait.
	 */
	status = acpi_ex_system_wait_mutex(
			acpi_gbl_global_lock_mutex->mutex.os_mutex, 0);
	if (status == AE_TIME) {
		if (acpi_ev_global_lock_thread_id == acpi_os_get_thread_id()) {
			acpi_ev_global_lock_acquired++;
			return AE_OK;
		}
	}

	if (ACPI_FAILURE(status)) {
		status = acpi_ex_system_wait_mutex(
				acpi_gbl_global_lock_mutex->mutex.os_mutex,
				timeout);
	}
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	acpi_ev_global_lock_thread_id = acpi_os_get_thread_id();
	acpi_ev_global_lock_acquired++;

	/*
	 * Update the global lock handle and check for wraparound. The handle is
	 * only used for the external global lock interfaces, but it is updated
	 * here to properly handle the case where a single thread may acquire the
	 * lock via both the AML and the acpi_acquire_global_lock interfaces. The
	 * handle is therefore updated on the first acquire from a given thread
	 * regardless of where the acquisition request originated.
	 */
	acpi_gbl_global_lock_handle++;
	if (acpi_gbl_global_lock_handle == 0) {
		acpi_gbl_global_lock_handle = 1;
	}

	/*
	 * Make sure that a global lock actually exists. If not, just treat the
	 * lock as a standard mutex.
	 */
	if (!acpi_gbl_global_lock_present) {
		acpi_gbl_global_lock_acquired = TRUE;
		return_ACPI_STATUS(AE_OK);
	}

	flags = acpi_os_acquire_lock(acpi_ev_global_lock_pending_lock);

	do {

		/* Attempt to acquire the actual hardware lock */

		ACPI_ACQUIRE_GLOBAL_LOCK(acpi_gbl_FACS, acquired);
		if (acquired) {
			acpi_gbl_global_lock_acquired = TRUE;

			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "Acquired hardware Global Lock\n"));
			break;
		}

		acpi_ev_global_lock_pending = TRUE;

		acpi_os_release_lock(acpi_ev_global_lock_pending_lock, flags);

		/*
		 * Did not get the lock. The pending bit was set above, and we
		 * must wait until we get the global lock released interrupt.
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Waiting for hardware Global Lock\n"));

		/*
		 * Wait for handshake with the global lock interrupt handler.
		 * This interface releases the interpreter if we must wait.
		 */
		status = acpi_ex_system_wait_semaphore(
						acpi_gbl_global_lock_semaphore,
						ACPI_WAIT_FOREVER);

		flags = acpi_os_acquire_lock(acpi_ev_global_lock_pending_lock);

	} while (ACPI_SUCCESS(status));

	acpi_ev_global_lock_pending = FALSE;

	acpi_os_release_lock(acpi_ev_global_lock_pending_lock, flags);

	return_ACPI_STATUS(status);
}