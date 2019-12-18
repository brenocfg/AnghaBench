#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ ipc_port_t ;
struct TYPE_6__ {scalar_t__ ith_self; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 scalar_t__ ipc_port_make_send (scalar_t__) ; 
 int /*<<< orphan*/  thread_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 

ipc_port_t
convert_thread_to_port(
	thread_t		thread)
{
	ipc_port_t		port;

	thread_mtx_lock(thread);

	if (thread->ith_self != IP_NULL)
		port = ipc_port_make_send(thread->ith_self);
	else
		port = IP_NULL;

	thread_mtx_unlock(thread);

	thread_deallocate(thread);

	return (port);
}