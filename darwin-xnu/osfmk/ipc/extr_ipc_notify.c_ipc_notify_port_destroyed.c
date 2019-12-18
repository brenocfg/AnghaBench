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
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  mach_notify_port_destroyed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_notify_port_destroyed(
	ipc_port_t	port,
	ipc_port_t	right)
{
	mach_notify_port_destroyed(port, right);
	/* send-once and receive rights consumed */
}