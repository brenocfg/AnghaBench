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
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  USRSTACK ; 
 int /*<<< orphan*/  USRSTACK64 ; 

kern_return_t
thread_userstackdefault(
	mach_vm_offset_t *default_user_stack,
	boolean_t is64bit)
{
	if (is64bit) {
		*default_user_stack = USRSTACK64;
	} else {
		*default_user_stack = USRSTACK;
	}

	return (KERN_SUCCESS);
}