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
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  integer_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ kernel_thread_create (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_start (int /*<<< orphan*/ ) ; 

kern_return_t
kernel_thread_start_priority(
	thread_continue_t	continuation,
	void				*parameter,
	integer_t			priority,
	thread_t			*new_thread)
{
	kern_return_t	result;
	thread_t		thread;

	result = kernel_thread_create(continuation, parameter, priority, &thread);
	if (result != KERN_SUCCESS)
		return (result);

	*new_thread = thread;	

	thread_mtx_lock(thread);
	thread_start(thread);
	thread_mtx_unlock(thread);

	return (result);
}