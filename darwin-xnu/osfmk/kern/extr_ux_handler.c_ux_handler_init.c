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
typedef  int /*<<< orphan*/  ipc_kobject_t ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_UX_HANDLER ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  ux_handler_kobject ; 
 scalar_t__ ux_handler_port ; 

void
ux_handler_init(void)
{
	ux_handler_port = ipc_port_alloc_kernel();

	if (ux_handler_port == IP_NULL)
		panic("can't allocate unix exception port");

	ipc_kobject_set(ux_handler_port, (ipc_kobject_t)&ux_handler_kobject, IKOT_UX_HANDLER);
}