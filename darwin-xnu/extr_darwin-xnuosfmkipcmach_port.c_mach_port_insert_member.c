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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_pset_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  scalar_t__ ipc_object_t ;

/* Variables and functions */
 scalar_t__ IO_NULL ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_PORT_SET ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAITQ_DONT_LOCK ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  io_unlock (scalar_t__) ; 
 scalar_t__ ipc_object_translate_two (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ ipc_pset_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_pset_lazy_allocate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_link_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_link_reserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_prepost_release_reserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_prepost_reserve (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_insert_member(
	ipc_space_t		space,
	mach_port_name_t	name,
	mach_port_name_t	psname)
{
	ipc_object_t obj;
	ipc_object_t psobj;
	kern_return_t kr;
	uint64_t wq_link_id;
	uint64_t wq_reserved_prepost;

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (!MACH_PORT_VALID(name) || !MACH_PORT_VALID(psname))
		return KERN_INVALID_RIGHT;

	wq_link_id = waitq_link_reserve(NULL);
	wq_reserved_prepost = waitq_prepost_reserve(NULL, 10,
						    WAITQ_DONT_LOCK);
	kr = ipc_pset_lazy_allocate(space, psname);
	if (kr != KERN_SUCCESS)
		goto done;


	kr = ipc_object_translate_two(space, 
				      name, MACH_PORT_RIGHT_RECEIVE, &obj,
				      psname, MACH_PORT_RIGHT_PORT_SET, &psobj);
	if (kr != KERN_SUCCESS)
		goto done;

	/* obj and psobj are locked (and were locked in that order) */
	assert(psobj != IO_NULL);
	assert(obj != IO_NULL);

	__IGNORE_WCASTALIGN(kr = ipc_pset_add((ipc_pset_t)psobj, (ipc_port_t)obj,
					    &wq_link_id, &wq_reserved_prepost));

	io_unlock(psobj);
	io_unlock(obj);

 done:
	/* on success, wq_link_id is reset to 0, so this is always safe */
	waitq_link_release(wq_link_id);
	waitq_prepost_release_reserve(wq_reserved_prepost);

	return kr;
}