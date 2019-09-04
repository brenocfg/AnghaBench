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
typedef  TYPE_1__* vnode_pager_t ;
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  scalar_t__ upl_size_t ;
typedef  int /*<<< orphan*/  upl_offset_t ;
struct TYPE_3__ {int /*<<< orphan*/  vnode_handle; } ;

/* Variables and functions */
 scalar_t__ MAX_UPL_TRANSFER_BYTES ; 
 scalar_t__ PAGE_SIZE ; 
 int UPL_IOSYNC ; 
 int UPL_KEEPCACHED ; 
 int UPL_MSYNC ; 
 int UPL_VNODE_PAGER ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int /*<<< orphan*/  vnode_pageout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int*) ; 
 scalar_t__ vnode_pager_get_filesize (int /*<<< orphan*/ ) ; 

void
vnode_pager_cluster_write(
	vnode_pager_t		vnode_object,
	vm_object_offset_t	offset,
	vm_size_t		cnt,
	vm_object_offset_t   *	resid_offset,
	int		     *  io_error,
	int			upl_flags)
{
	vm_size_t	size;
	int		errno;

	if (upl_flags & UPL_MSYNC) {

	        upl_flags |= UPL_VNODE_PAGER;

		if ( (upl_flags & UPL_IOSYNC) && io_error)
		        upl_flags |= UPL_KEEPCACHED;

	        while (cnt) {
			size = (cnt < MAX_UPL_TRANSFER_BYTES) ? cnt : MAX_UPL_TRANSFER_BYTES; /* effective max */

			assert((upl_size_t) size == size);
			vnode_pageout(vnode_object->vnode_handle, 
				      NULL, (upl_offset_t)0, offset, (upl_size_t)size, upl_flags, &errno);

			if ( (upl_flags & UPL_KEEPCACHED) ) {
			        if ( (*io_error = errno) )
				        break;
			}
			cnt    -= size;
			offset += size;
		}
		if (resid_offset)
			*resid_offset = offset;

	} else {
	        vm_object_offset_t      vnode_size;
	        vm_object_offset_t	base_offset;

	        /*
		 * this is the pageout path
		 */
		vnode_size = vnode_pager_get_filesize(vnode_object->vnode_handle);

		if (vnode_size > (offset + PAGE_SIZE)) {
		        /*
			 * preset the maximum size of the cluster
			 * and put us on a nice cluster boundary...
			 * and then clip the size to insure we
			 * don't request past the end of the underlying file
			 */
		        size = MAX_UPL_TRANSFER_BYTES;
		        base_offset = offset & ~((signed)(size - 1));

			if ((base_offset + size) > vnode_size)
			        size = round_page(((vm_size_t)(vnode_size - base_offset)));
		} else {
		        /*
			 * we've been requested to page out a page beyond the current
			 * end of the 'file'... don't try to cluster in this case...
			 * we still need to send this page through because it might
			 * be marked precious and the underlying filesystem may need
			 * to do something with it (besides page it out)...
			 */
		        base_offset = offset;
			size = PAGE_SIZE;
		}
		assert((upl_size_t) size == size);
	        vnode_pageout(vnode_object->vnode_handle,
			      NULL, (upl_offset_t)(offset - base_offset), base_offset, (upl_size_t) size,
			      (upl_flags & UPL_IOSYNC) | UPL_VNODE_PAGER, NULL);
	}
}