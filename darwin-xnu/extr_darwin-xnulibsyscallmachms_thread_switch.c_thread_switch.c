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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  mach_msg_timeout_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  syscall_thread_switch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

kern_return_t
thread_switch(
	mach_port_t thread,
	int option,
	mach_msg_timeout_t option_time)
{
	kern_return_t result;
	
	result = syscall_thread_switch(thread, option, option_time);
	return result;
}