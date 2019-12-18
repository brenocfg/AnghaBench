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
typedef  scalar_t__ ipc_port_t ;
typedef  TYPE_1__* clock_t ;
struct TYPE_3__ {scalar_t__ cl_control; scalar_t__ cl_service; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ipc_clock_init(
	clock_t		clock)
{
	ipc_port_t	port;

	port = ipc_port_alloc_kernel();
	if (port == IP_NULL)
		panic("ipc_clock_init");
	clock->cl_service = port;

	port = ipc_port_alloc_kernel();
	if (port == IP_NULL)
		panic("ipc_clock_init");
	clock->cl_control = port;
}