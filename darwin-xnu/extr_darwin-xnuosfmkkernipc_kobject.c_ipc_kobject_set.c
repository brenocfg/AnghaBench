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
typedef  int /*<<< orphan*/  ipc_kobject_type_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;

/* Variables and functions */
 int /*<<< orphan*/  ip_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_kobject_set(
	ipc_port_t			port,
	ipc_kobject_t		kobject,
	ipc_kobject_type_t	type)
{
	ip_lock(port);
	ipc_kobject_set_atomically(port, kobject, type);
	ip_unlock(port);
}