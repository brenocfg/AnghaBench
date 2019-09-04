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
typedef  scalar_t__ ipc_port_t ;
typedef  scalar_t__ ipc_object_t ;

/* Variables and functions */
 unsigned int IOT_PORT ; 
 int /*<<< orphan*/  io_lock_destroy (scalar_t__) ; 
 int /*<<< orphan*/ * ipc_object_zones ; 
 int /*<<< orphan*/  ipc_port_finalize (scalar_t__) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,scalar_t__) ; 

void
io_free(
	unsigned int	otype,
	ipc_object_t	object)
{
	ipc_port_t	port;

	if (otype == IOT_PORT) {
		port = (ipc_port_t) object;
		ipc_port_finalize(port);
	}
	io_lock_destroy(object);
	zfree(ipc_object_zones[otype], object);
}