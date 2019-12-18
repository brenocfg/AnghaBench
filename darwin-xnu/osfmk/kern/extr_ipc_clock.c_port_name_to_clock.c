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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  scalar_t__ clock_t ;
struct TYPE_6__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ CLOCK_NULL ; 
 scalar_t__ IKOT_CLOCK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  current_space () ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 scalar_t__ ipc_port_translate_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 

clock_t
port_name_to_clock(
	mach_port_name_t clock_name)
{
	clock_t		clock = CLOCK_NULL;
	ipc_space_t	space;
	ipc_port_t	port;

	if (clock_name == 0)
		return (clock);
	space = current_space();
	if (ipc_port_translate_send(space, clock_name, &port) != KERN_SUCCESS)
		return (clock);
	if (ip_active(port) && (ip_kotype(port) == IKOT_CLOCK))
		clock = (clock_t) port->ip_kobject;
	ip_unlock(port);
	return (clock);
}