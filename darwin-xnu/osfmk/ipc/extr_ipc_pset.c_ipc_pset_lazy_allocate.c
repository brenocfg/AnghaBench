#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct waitq_set {int dummy; } ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_pset_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_2__* ipc_mqueue_t ;
typedef  TYPE_3__* ipc_entry_t ;
struct TYPE_8__ {int ie_bits; scalar_t__ ie_object; } ;
struct TYPE_7__ {struct waitq_set imq_set_queue; } ;
struct TYPE_6__ {TYPE_2__ ips_messages; } ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACH_PORT_TYPE_PORT_SET ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_reference (scalar_t__) ; 
 int /*<<< orphan*/  io_release (scalar_t__) ; 
 scalar_t__ ipc_right_lookup_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  is_read_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_set_lazy_init_link (struct waitq_set*) ; 

kern_return_t
ipc_pset_lazy_allocate(
	ipc_space_t space,
	mach_port_name_t psname)
{
	kern_return_t kr;
	ipc_entry_t entry;
	ipc_object_t psobj;
	ipc_pset_t pset;

	kr = ipc_right_lookup_read(space, psname, &entry);
	if (kr != KERN_SUCCESS)
		return kr;

	/* space is read-locked and active */
	if ((entry->ie_bits & MACH_PORT_TYPE_PORT_SET) == 0) {
		is_read_unlock(space);
		kr = KERN_INVALID_RIGHT;
		return kr;
	}

	psobj = entry->ie_object;
	__IGNORE_WCASTALIGN(pset = (ipc_pset_t) psobj);
	assert(pset != NULL);
	ipc_mqueue_t set_mqueue = &pset->ips_messages;
	struct waitq_set *wqset =  &set_mqueue->imq_set_queue;

	io_reference(psobj);
	is_read_unlock(space);

	/*
	 * lazily initialize the wqset to avoid
	 * possible allocation while linking
	 * under spinlocks.
	 */
	waitq_set_lazy_init_link(wqset);
	io_release(psobj);

	return KERN_SUCCESS;
}