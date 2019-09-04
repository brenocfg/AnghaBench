#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clock_sleep_trap_args {scalar_t__ clock_name; int sleep_sec; int sleep_nsec; int /*<<< orphan*/  wakeup_time; int /*<<< orphan*/  sleep_type; } ;
typedef  int /*<<< orphan*/  sleep_type_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
struct TYPE_3__ {int tv_sec; int tv_nsec; } ;
typedef  TYPE_1__ mach_timespec_t ;
typedef  scalar_t__ mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/ * clock_t ;

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ MACH_PORT_NULL ; 
 size_t SYSTEM_CLOCK ; 
 int /*<<< orphan*/ * clock_list ; 
 scalar_t__ clock_sleep_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  copyout (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * port_name_to_clock (scalar_t__) ; 

kern_return_t
clock_sleep_trap(
	struct clock_sleep_trap_args *args)
{
	mach_port_name_t	clock_name = args->clock_name;
	sleep_type_t		sleep_type = args->sleep_type;
	int					sleep_sec = args->sleep_sec;
	int					sleep_nsec = args->sleep_nsec;
	mach_vm_address_t	wakeup_time_addr = args->wakeup_time;  
	clock_t				clock;
	mach_timespec_t		swtime = {};
	kern_return_t		rvalue;

	/*
	 * Convert the trap parameters.
	 */
	if (clock_name == MACH_PORT_NULL)
		clock = &clock_list[SYSTEM_CLOCK];
	else
		clock = port_name_to_clock(clock_name);

	swtime.tv_sec  = sleep_sec;
	swtime.tv_nsec = sleep_nsec;

	/*
	 * Call the actual clock_sleep routine.
	 */
	rvalue = clock_sleep_internal(clock, sleep_type, &swtime);

	/*
	 * Return current time as wakeup time.
	 */
	if (rvalue != KERN_INVALID_ARGUMENT && rvalue != KERN_FAILURE) {
		copyout((char *)&swtime, wakeup_time_addr, sizeof(mach_timespec_t));
	}
	return (rvalue);
}