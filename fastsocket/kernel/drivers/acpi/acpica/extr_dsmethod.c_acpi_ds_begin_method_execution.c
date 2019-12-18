#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ thread_count; int method_flags; scalar_t__ sync_level; TYPE_3__* mutex; int /*<<< orphan*/  owner_id; } ;
union acpi_operand_object {TYPE_4__ method; } ;
struct acpi_walk_state {TYPE_1__* thread; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {scalar_t__ sync_level; scalar_t__ thread_id; scalar_t__ original_sync_level; int /*<<< orphan*/  os_mutex; int /*<<< orphan*/  acquisition_depth; } ;
struct TYPE_7__ {TYPE_2__ mutex; } ;
struct TYPE_5__ {scalar_t__ current_sync_level; scalar_t__ thread_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 scalar_t__ ACPI_UINT8_MAX ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_AML_METHOD_LIMIT ; 
 int /*<<< orphan*/  AE_AML_MUTEX_ORDER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NULL_ENTRY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AML_METHOD_SERIALIZED ; 
 int /*<<< orphan*/  acpi_ds_create_method_mutex (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ex_system_wait_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_allocate_owner_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ds_begin_method_execution ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_begin_method_execution(struct acpi_namespace_node *method_node,
			       union acpi_operand_object *obj_desc,
			       struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ds_begin_method_execution, method_node);

	if (!method_node) {
		return_ACPI_STATUS(AE_NULL_ENTRY);
	}

	/* Prevent wraparound of thread count */

	if (obj_desc->method.thread_count == ACPI_UINT8_MAX) {
		ACPI_ERROR((AE_INFO,
			    "Method reached maximum reentrancy limit (255)"));
		return_ACPI_STATUS(AE_AML_METHOD_LIMIT);
	}

	/*
	 * If this method is serialized, we need to acquire the method mutex.
	 */
	if (obj_desc->method.method_flags & AML_METHOD_SERIALIZED) {
		/*
		 * Create a mutex for the method if it is defined to be Serialized
		 * and a mutex has not already been created. We defer the mutex creation
		 * until a method is actually executed, to minimize the object count
		 */
		if (!obj_desc->method.mutex) {
			status = acpi_ds_create_method_mutex(obj_desc);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}
		}

		/*
		 * The current_sync_level (per-thread) must be less than or equal to
		 * the sync level of the method. This mechanism provides some
		 * deadlock prevention
		 *
		 * Top-level method invocation has no walk state at this point
		 */
		if (walk_state &&
		    (walk_state->thread->current_sync_level >
		     obj_desc->method.mutex->mutex.sync_level)) {
			ACPI_ERROR((AE_INFO,
				    "Cannot acquire Mutex for method [%4.4s], current SyncLevel is too large (%d)",
				    acpi_ut_get_node_name(method_node),
				    walk_state->thread->current_sync_level));

			return_ACPI_STATUS(AE_AML_MUTEX_ORDER);
		}

		/*
		 * Obtain the method mutex if necessary. Do not acquire mutex for a
		 * recursive call.
		 */
		if (!walk_state ||
		    !obj_desc->method.mutex->mutex.thread_id ||
		    (walk_state->thread->thread_id !=
		     obj_desc->method.mutex->mutex.thread_id)) {
			/*
			 * Acquire the method mutex. This releases the interpreter if we
			 * block (and reacquires it before it returns)
			 */
			status =
			    acpi_ex_system_wait_mutex(obj_desc->method.mutex->
						      mutex.os_mutex,
						      ACPI_WAIT_FOREVER);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}

			/* Update the mutex and walk info and save the original sync_level */

			if (walk_state) {
				obj_desc->method.mutex->mutex.
				    original_sync_level =
				    walk_state->thread->current_sync_level;

				obj_desc->method.mutex->mutex.thread_id =
				    walk_state->thread->thread_id;
				walk_state->thread->current_sync_level =
				    obj_desc->method.sync_level;
			} else {
				obj_desc->method.mutex->mutex.
				    original_sync_level =
				    obj_desc->method.mutex->mutex.sync_level;
			}
		}

		/* Always increase acquisition depth */

		obj_desc->method.mutex->mutex.acquisition_depth++;
	}

	/*
	 * Allocate an Owner ID for this method, only if this is the first thread
	 * to begin concurrent execution. We only need one owner_id, even if the
	 * method is invoked recursively.
	 */
	if (!obj_desc->method.owner_id) {
		status = acpi_ut_allocate_owner_id(&obj_desc->method.owner_id);
		if (ACPI_FAILURE(status)) {
			goto cleanup;
		}
	}

	/*
	 * Increment the method parse tree thread count since it has been
	 * reentered one more time (even if it is the same thread)
	 */
	obj_desc->method.thread_count++;
	return_ACPI_STATUS(status);

      cleanup:
	/* On error, must release the method mutex (if present) */

	if (obj_desc->method.mutex) {
		acpi_os_release_mutex(obj_desc->method.mutex->mutex.os_mutex);
	}
	return_ACPI_STATUS(status);
}