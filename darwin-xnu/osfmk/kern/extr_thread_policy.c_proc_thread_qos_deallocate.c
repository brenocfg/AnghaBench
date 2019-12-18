#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct thread_qos_override {struct thread_qos_override* override_next; } ;
struct TYPE_6__ {scalar_t__ thrp_qos_ipc_override; scalar_t__ thrp_qos_sync_ipc_override; scalar_t__ thrp_qos_override; } ;
struct TYPE_7__ {scalar_t__ ipc_overrides; scalar_t__ sync_ipc_overrides; TYPE_1__ requested_policy; struct thread_qos_override* overrides; } ;

/* Variables and functions */
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_qos_override_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct thread_qos_override*) ; 

void proc_thread_qos_deallocate(thread_t thread)
{
	/* This thread must have no more IPC overrides. */
	assert(thread->ipc_overrides == 0);
	assert(thread->requested_policy.thrp_qos_ipc_override == THREAD_QOS_UNSPECIFIED);
	assert(thread->sync_ipc_overrides == 0);
	assert(thread->requested_policy.thrp_qos_sync_ipc_override == THREAD_QOS_UNSPECIFIED);

	/*
	 * Clear out any lingering override objects.
	 */
	struct thread_qos_override *override;

	thread_mtx_lock(thread);
	override = thread->overrides;
	thread->overrides = NULL;
	thread->requested_policy.thrp_qos_override = THREAD_QOS_UNSPECIFIED;
	/* We don't need to re-evaluate thread policy here because the thread has already exited */
	thread_mtx_unlock(thread);

	while (override) {
		struct thread_qos_override *override_next = override->override_next;

		zfree(thread_qos_override_zone, override);
		override = override_next;
	}
}