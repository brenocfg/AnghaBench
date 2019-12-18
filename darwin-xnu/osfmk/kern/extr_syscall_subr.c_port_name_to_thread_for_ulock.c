#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_9__ {TYPE_1__* task; } ;
struct TYPE_8__ {int /*<<< orphan*/  itk_space; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 TYPE_2__* THREAD_NULL ; 
 TYPE_2__* convert_port_to_thread (int /*<<< orphan*/ ) ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  ip_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_translate_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_deallocate (TYPE_2__*) ; 

thread_t
port_name_to_thread_for_ulock(mach_port_name_t thread_name)
{
	thread_t thread = THREAD_NULL;
	thread_t self = current_thread();

	/*
	 * Translate the port name if supplied.
	 */
	if (thread_name != MACH_PORT_NULL) {
		ipc_port_t port;

		if (ipc_port_translate_send(self->task->itk_space,
		                            thread_name, &port) == KERN_SUCCESS) {
			ip_reference(port);
			ip_unlock(port);

			thread = convert_port_to_thread(port);
			ip_release(port);

			if (thread == THREAD_NULL) {
				return thread;
			}

			if ((thread == self) || (thread->task != self->task)) {
				thread_deallocate(thread);
				thread = THREAD_NULL;
			}
		}
	}

	return thread;
}