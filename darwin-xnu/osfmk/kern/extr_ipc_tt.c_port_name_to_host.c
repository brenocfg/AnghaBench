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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  host_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_NULL ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_port_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_space () ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_translate_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

host_t
port_name_to_host(
	mach_port_name_t name)
{

	host_t host = HOST_NULL;
	kern_return_t kr;
	ipc_port_t port;

	if (MACH_PORT_VALID(name)) {
		kr = ipc_port_translate_send(current_space(), name, &port);
		if (kr == KERN_SUCCESS) {
			host = convert_port_to_host(port);
			ip_unlock(port);
		}
	}
	return host;
}