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

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kernel_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lt_bound_thread ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lt_start_lock_thread_bound(thread_continue_t func)
{
	thread_t thread;
	kern_return_t kr;

	kr = kernel_thread_start(lt_bound_thread, func, &thread);
	assert(kr == KERN_SUCCESS);

	thread_deallocate(thread);
}