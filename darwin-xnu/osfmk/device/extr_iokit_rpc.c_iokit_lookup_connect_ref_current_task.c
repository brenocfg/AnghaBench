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
typedef  int /*<<< orphan*/  io_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_IOKIT_CONNECT ; 
 int /*<<< orphan*/  current_space () ; 
 int /*<<< orphan*/  iokit_lookup_object_in_space_with_port_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

io_object_t
iokit_lookup_connect_ref_current_task(mach_port_name_t name)
{
    return (iokit_lookup_object_in_space_with_port_name(name, IKOT_IOKIT_CONNECT, current_space()));
}