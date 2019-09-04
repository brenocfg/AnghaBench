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
 int /*<<< orphan*/  BASEPRI_VM ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ kernel_thread_start_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_reaper_thread ; 

void
vm_object_reaper_init(void)
{
	kern_return_t	kr;
	thread_t	thread;

	kr = kernel_thread_start_priority(
		(thread_continue_t) vm_object_reaper_thread,
		NULL,
		BASEPRI_VM,
		&thread);
	if (kr != KERN_SUCCESS) {
		panic("failed to launch vm_object_reaper_thread kr=0x%x", kr);
	}
	thread_deallocate(thread);
}