#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* atm_task_descriptor_t ;
struct TYPE_5__ {scalar_t__ reference_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  trace_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atm_descriptors_zone ; 
 int /*<<< orphan*/  atm_lock_grp ; 
 scalar_t__ atm_task_desc_release_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
atm_task_descriptor_dealloc(atm_task_descriptor_t task_descriptor)
{
	if (0 < atm_task_desc_release_internal(task_descriptor)) {
		return;
	}

	assert(task_descriptor->reference_count == 0);

#if DEVELOPMENT || DEBUG
	lck_mtx_lock(&atm_descriptors_list_lock);
	queue_remove(&atm_descriptors_list, task_descriptor, atm_task_descriptor_t, descriptor_elt);
	lck_mtx_unlock(&atm_descriptors_list_lock);
#endif
	/* release the send right for the named memory entry */
	ipc_port_release_send(task_descriptor->trace_buffer);
	lck_mtx_destroy(&task_descriptor->lock, &atm_lock_grp);
	zfree(atm_descriptors_zone, task_descriptor);
	return;
}