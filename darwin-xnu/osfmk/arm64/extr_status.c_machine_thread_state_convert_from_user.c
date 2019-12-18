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
typedef  int /*<<< orphan*/  thread_state_t ;
typedef  int /*<<< orphan*/  thread_flavor_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 

kern_return_t
machine_thread_state_convert_from_user(
			 thread_t thread,
			 thread_flavor_t flavor,
			 thread_state_t tstate,
			 mach_msg_type_number_t count)
{
	// No conversion from userspace representation on this platform
	(void)thread; (void)flavor; (void)tstate; (void)count;
	return KERN_SUCCESS;
}