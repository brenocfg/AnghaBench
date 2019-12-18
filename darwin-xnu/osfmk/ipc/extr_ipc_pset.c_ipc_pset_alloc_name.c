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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_pset_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  ips_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOT_PORT_SET ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_TYPE_PORT_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ipc_mqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_object_alloc_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
ipc_pset_alloc_name(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_pset_t		*psetp)
{
	ipc_pset_t pset;
	kern_return_t kr;

	kr = ipc_object_alloc_name(space, IOT_PORT_SET,
				   MACH_PORT_TYPE_PORT_SET, 0,
				   name, (ipc_object_t *) &pset);
	if (kr != KERN_SUCCESS) {
		return kr;
	}
	/* pset is locked */

	ipc_mqueue_init(&pset->ips_messages, TRUE /* set */);

	*psetp = pset;
	return KERN_SUCCESS;
}