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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_type_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;
typedef  scalar_t__ io_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  iokit_lock_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iokit_unlock_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kobject_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
iokit_switch_object_port( ipc_port_t port, io_object_t obj, ipc_kobject_type_t type )
{
    iokit_lock_port(port);
    ipc_kobject_set( port, (ipc_kobject_t) obj, type);
    iokit_unlock_port(port);

    return( KERN_SUCCESS);
}