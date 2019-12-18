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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  ipc_kobject_type_t ;
typedef  int /*<<< orphan*/  io_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  itk_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  iokit_lookup_object_in_space_with_port_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

io_object_t
iokit_lookup_object_with_port_name(mach_port_name_t name, ipc_kobject_type_t type, task_t task)
{
    return (iokit_lookup_object_in_space_with_port_name(name, type, task->itk_space));
}