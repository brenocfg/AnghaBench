#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ memory_object_size_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_6__ {TYPE_1__* v_ubcinfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  ui_control; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int MEMORY_OBJECT_DATA_FLUSH ; 
 int MEMORY_OBJECT_DATA_NO_CHANGE ; 
 int MEMORY_OBJECT_IO_SYNC ; 
 int MEMORY_OBJECT_RETURN_ALL ; 
 int MEMORY_OBJECT_RETURN_DIRTY ; 
 int MEMORY_OBJECT_RETURN_NONE ; 
 int /*<<< orphan*/  UBCINFOEXISTS (TYPE_2__*) ; 
 int UBC_INVALIDATE ; 
 int UBC_PUSHALL ; 
 int UBC_PUSHDIRTY ; 
 int UBC_SYNC ; 
 int /*<<< orphan*/  VM_PROT_NO_CHANGE ; 
 scalar_t__ memory_object_lock_request (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ round_page_64 (scalar_t__) ; 
 scalar_t__ trunc_page_64 (scalar_t__) ; 

__attribute__((used)) static int
ubc_msync_internal(vnode_t vp, off_t beg_off, off_t end_off, off_t *resid_off, int flags, int *io_errno)
{
	memory_object_size_t	tsize;
	kern_return_t		kret;
	int request_flags = 0;
	int flush_flags   = MEMORY_OBJECT_RETURN_NONE;
	
	if ( !UBCINFOEXISTS(vp))
	        return (0);
	if ((flags & (UBC_INVALIDATE | UBC_PUSHDIRTY | UBC_PUSHALL)) == 0)
	        return (0);
	if (end_off <= beg_off)
	        return (1);

	if (flags & UBC_INVALIDATE)
	        /*
		 * discard the resident pages
		 */
		request_flags = (MEMORY_OBJECT_DATA_FLUSH | MEMORY_OBJECT_DATA_NO_CHANGE);

	if (flags & UBC_SYNC)
	        /*
		 * wait for all the I/O to complete before returning
		 */
	        request_flags |= MEMORY_OBJECT_IO_SYNC;

	if (flags & UBC_PUSHDIRTY)
	        /*
		 * we only return the dirty pages in the range
		 */
	        flush_flags = MEMORY_OBJECT_RETURN_DIRTY;

	if (flags & UBC_PUSHALL)
	        /*
		 * then return all the interesting pages in the range (both
		 * dirty and precious) to the pager
		 */
	        flush_flags = MEMORY_OBJECT_RETURN_ALL;

	beg_off = trunc_page_64(beg_off);
	end_off = round_page_64(end_off);
	tsize   = (memory_object_size_t)end_off - beg_off;

	/* flush and/or invalidate pages in the range requested */
	kret = memory_object_lock_request(vp->v_ubcinfo->ui_control,
					  beg_off, tsize,
					  (memory_object_offset_t *)resid_off,
					  io_errno, flush_flags, request_flags,
					  VM_PROT_NO_CHANGE);
	
	return ((kret == KERN_SUCCESS) ? 1 : 0);
}