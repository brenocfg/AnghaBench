#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_8__ {int /*<<< orphan*/  io_bits; } ;
struct TYPE_7__ {int ip_references; TYPE_4__ ip_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOT_PORT ; 
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ io_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_lock_init (TYPE_4__*) ; 
 int /*<<< orphan*/  io_makebits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

ipc_port_t
ipc_port_alloc_special(
	ipc_space_t	space)
{
	ipc_port_t port;

	__IGNORE_WCASTALIGN(port = (ipc_port_t) io_alloc(IOT_PORT));
	if (port == IP_NULL)
		return IP_NULL;

#if     MACH_ASSERT
	uintptr_t buf[IP_CALLSTACK_MAX];
	ipc_port_callstack_init_debug(&buf[0], IP_CALLSTACK_MAX);
#endif /* MACH_ASSERT */	

	bzero((char *)port, sizeof(*port));
	io_lock_init(&port->ip_object);
	port->ip_references = 1;
	port->ip_object.io_bits = io_makebits(TRUE, IOT_PORT, 0);

	ipc_port_init(port, space, 1);

#if     MACH_ASSERT
	ipc_port_init_debug(port, &buf[0], IP_CALLSTACK_MAX);
#endif  /* MACH_ASSERT */		

	return port;
}