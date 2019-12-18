#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ task_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {scalar_t__ task; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int ESRCH ; 
 scalar_t__ FALSE ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMP_USYNCH_ADD_OVERRIDE ; 
 int /*<<< orphan*/  IMP_USYNCH_QOS_OVERRIDE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* THREAD_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int proc_thread_qos_add_override_internal (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* task_findtid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_deallocate (TYPE_1__*) ; 

int
proc_thread_qos_add_override(task_t           task,
                             thread_t         thread,
                             uint64_t         tid,
                             int              override_qos,
                             boolean_t        first_override_for_resource,
                             user_addr_t      resource,
                             int              resource_type)
{
	boolean_t has_thread_reference = FALSE;
	int rc = 0;

	if (thread == THREAD_NULL) {
		thread = task_findtid(task, tid);
		/* returns referenced thread */

		if (thread == THREAD_NULL) {
			KERNEL_DEBUG_CONSTANT((IMPORTANCE_CODE(IMP_USYNCH_QOS_OVERRIDE, IMP_USYNCH_ADD_OVERRIDE)) | DBG_FUNC_NONE,
								  tid, 0, 0xdead, 0, 0);
			return ESRCH;
		}
		has_thread_reference = TRUE;
	} else {
		assert(thread->task == task);
	}
	rc = proc_thread_qos_add_override_internal(thread, override_qos,
			first_override_for_resource, resource, resource_type);
	if (has_thread_reference) {
		thread_deallocate(thread);
	}

	return rc;
}