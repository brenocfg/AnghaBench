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
struct TYPE_5__ {scalar_t__ sync_level; int acquisition_depth; scalar_t__ original_sync_level; TYPE_3__* owner_thread; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {scalar_t__ value; } ;
union acpi_operand_object {TYPE_2__ mutex; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u16 ;
struct acpi_walk_state {TYPE_3__* thread; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {scalar_t__ current_sync_level; int /*<<< orphan*/  thread_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_MUTEX_ORDER ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_ex_acquire_mutex_object (int /*<<< orphan*/ ,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_link_mutex (union acpi_operand_object*,TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_acquire_mutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_acquire_mutex(union acpi_operand_object *time_desc,
		      union acpi_operand_object *obj_desc,
		      struct acpi_walk_state *walk_state)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_acquire_mutex, obj_desc);

	if (!obj_desc) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Must have a valid thread ID */

	if (!walk_state->thread) {
		ACPI_ERROR((AE_INFO,
			    "Cannot acquire Mutex [%4.4s], null thread info",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		return_ACPI_STATUS(AE_AML_INTERNAL);
	}

	/*
	 * Current sync level must be less than or equal to the sync level of the
	 * mutex. This mechanism provides some deadlock prevention
	 */
	if (walk_state->thread->current_sync_level > obj_desc->mutex.sync_level) {
		ACPI_ERROR((AE_INFO,
			    "Cannot acquire Mutex [%4.4s], current SyncLevel is too large (%d)",
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    walk_state->thread->current_sync_level));
		return_ACPI_STATUS(AE_AML_MUTEX_ORDER);
	}

	status = acpi_ex_acquire_mutex_object((u16) time_desc->integer.value,
					      obj_desc,
					      walk_state->thread->thread_id);
	if (ACPI_SUCCESS(status) && obj_desc->mutex.acquisition_depth == 1) {

		/* Save Thread object, original/current sync levels */

		obj_desc->mutex.owner_thread = walk_state->thread;
		obj_desc->mutex.original_sync_level =
		    walk_state->thread->current_sync_level;
		walk_state->thread->current_sync_level =
		    obj_desc->mutex.sync_level;

		/* Link the mutex to the current thread for force-unlock at method exit */

		acpi_ex_link_mutex(obj_desc, walk_state->thread);
	}

	return_ACPI_STATUS(status);
}