#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_right_t ;
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ mach_port_qos_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  mach_port_allocate_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

kern_return_t
mach_port_allocate_qos(
	ipc_space_t		space,
	mach_port_right_t	right,
	mach_port_qos_t		*qosp,
	mach_port_name_t	*namep)
{
	kern_return_t		kr;

	if (qosp->name)
		return KERN_INVALID_ARGUMENT;
	kr = mach_port_allocate_full (space, right, MACH_PORT_NULL,
					qosp, namep);
	return (kr);
}