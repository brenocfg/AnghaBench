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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_thread_start_priority (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 

kern_return_t
kernel_thread_start(
	thread_continue_t	continuation,
	void				*parameter,
	thread_t			*new_thread)
{
	return kernel_thread_start_priority(continuation, parameter, -1, new_thread);
}