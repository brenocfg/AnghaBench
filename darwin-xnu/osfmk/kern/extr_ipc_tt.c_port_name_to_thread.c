#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;

/* Variables and functions */
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_COPY_SEND ; 
 scalar_t__ MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_NULL ; 
 int /*<<< orphan*/  convert_port_to_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_space () ; 
 scalar_t__ ipc_object_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 

thread_t
port_name_to_thread(
	mach_port_name_t	name)
{
	thread_t	thread = THREAD_NULL;
	ipc_port_t	kport;

	if (MACH_PORT_VALID(name)) {
		if (ipc_object_copyin(current_space(), name,
					       MACH_MSG_TYPE_COPY_SEND,
							  (ipc_object_t *)&kport) != KERN_SUCCESS)
			return (THREAD_NULL);

		thread = convert_port_to_thread(kport);
		
		if (IP_VALID(kport))
			ipc_port_release_send(kport);
	}

	return (thread);
}