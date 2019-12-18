#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_pager_t ;
typedef  int vm_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  int /*<<< orphan*/ * upl_t ;
typedef  int upl_size_t ;
typedef  int /*<<< orphan*/  upl_offset_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  mo_control; } ;
struct TYPE_5__ {TYPE_1__ vn_pgr_hdr; int /*<<< orphan*/  vnode_handle; } ;

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int PAGE_MASK ; 
 int UPL_CLEAN_IN_PLACE ; 
 int UPL_IOSTREAMING ; 
 int UPL_NO_SYNC ; 
 int UPL_SET_INTERNAL ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memory_object_upl_request (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,unsigned int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_deallocate (int /*<<< orphan*/ *) ; 
 int vnode_pagein (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int,int*) ; 

kern_return_t
vnode_pager_cluster_read(
	vnode_pager_t		vnode_object,
	vm_object_offset_t	base_offset,
	vm_object_offset_t	offset,
	uint32_t		io_streaming,
	vm_size_t		cnt)
{
	int		local_error = 0;
	int		kret;
	int		flags = 0;

	assert(! (cnt & PAGE_MASK));

	if (io_streaming)
		flags |= UPL_IOSTREAMING;

	assert((upl_size_t) cnt == cnt);
	kret = vnode_pagein(vnode_object->vnode_handle,
			    (upl_t) NULL,
			    (upl_offset_t) (offset - base_offset),
			    base_offset,
			    (upl_size_t) cnt,
			    flags,
			    &local_error);
/*
	if(kret == PAGER_ABSENT) {
	Need to work out the defs here, 1 corresponds to PAGER_ABSENT 
	defined in bsd/vm/vm_pager.h  However, we should not be including 
	that file here it is a layering violation.
*/
	if (kret == 1) {
		int	uplflags;
		upl_t	upl = NULL;
		unsigned int	count = 0;
		kern_return_t	kr;

		uplflags = (UPL_NO_SYNC |
			    UPL_CLEAN_IN_PLACE |
			    UPL_SET_INTERNAL);
		count = 0;
		assert((upl_size_t) cnt == cnt);
		kr = memory_object_upl_request(vnode_object->vn_pgr_hdr.mo_control,
					       base_offset, (upl_size_t) cnt,
					       &upl, NULL, &count, uplflags, VM_KERN_MEMORY_NONE);
		if (kr == KERN_SUCCESS) {
			upl_abort(upl, 0);
			upl_deallocate(upl);
		} else {
			/*
			 * We couldn't gather the page list, probably
			 * because the memory object doesn't have a link
			 * to a VM object anymore (forced unmount, for
			 * example).  Just return an error to the vm_fault()
			 * path and let it handle it.
			 */
		}

		return KERN_FAILURE;
	}

	return KERN_SUCCESS;

}