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
struct mk_timer_destroy_trap_args {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 scalar_t__ IKOT_TIMER ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  current_space () ; 
 scalar_t__ ip_kotype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_translate_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mach_port_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mk_timer_destroy_trap(
	struct mk_timer_destroy_trap_args *args)
{
	mach_port_name_t	name = args->name;
	ipc_space_t			myspace = current_space();
	ipc_port_t			port;
	kern_return_t		result;

	result = ipc_port_translate_receive(myspace, name, &port);
	if (result != KERN_SUCCESS)
		return (result);

	if (ip_kotype(port) == IKOT_TIMER) {
		ip_unlock(port);
		result = mach_port_destroy(myspace, name);
	}
	else {
		ip_unlock(port);
		result = KERN_INVALID_ARGUMENT;
	}

	return (result);
}