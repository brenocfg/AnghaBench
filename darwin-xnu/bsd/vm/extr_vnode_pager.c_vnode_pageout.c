#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_object_offset_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/ * upl_t ;
typedef  int upl_size_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int upl_offset_t ;
struct vnode {scalar_t__ v_tag; TYPE_2__* v_mount; } ;
typedef  int pager_return_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  daddr64_t ;
struct TYPE_4__ {TYPE_1__* mnt_vtable; } ;
struct TYPE_3__ {int vfc_vfsflags; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_VM ; 
 int EINVAL ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int PAGER_ERROR ; 
 int PAGER_SUCCESS ; 
 int PAGE_SIZE ; 
 scalar_t__ UBCINFOEXISTS (struct vnode*) ; 
 int /*<<< orphan*/  UPL_ABORT_FREE_ON_EMPTY ; 
 int /*<<< orphan*/  UPL_COMMIT_FREE_ON_EMPTY ; 
 int UPL_MSYNC ; 
 int UPL_NOCOMMIT ; 
 int UPL_RET_ONLY_DIRTY ; 
 int UPL_UBC_MSYNC ; 
 int UPL_UBC_PAGEOUT ; 
 int UPL_VNODE_PAGER ; 
 int VFC_VFSVNOP_PAGEOUTV2 ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int VNOP_PAGEOUT (struct vnode*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ VT_NFS ; 
 int buf_invalblkno (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_buf_page_inval (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ubc_create_upl_kernel (struct vnode*,scalar_t__,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ubc_getsize (struct vnode*) ; 
 int /*<<< orphan*/  ubc_offtoblk (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_upl_abort_range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_upl_commit_range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ubc_upl_pageinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upl_dirty_page (int /*<<< orphan*/ *,int) ; 
 scalar_t__ upl_page_present (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfs_context_current () ; 

pager_return_t
vnode_pageout(struct vnode *vp,
	upl_t			upl,
	upl_offset_t		upl_offset,
	vm_object_offset_t	f_offset,
	upl_size_t		size,
	int			flags,
	int			*errorp)
{
	int		result = PAGER_SUCCESS;
	int		error = 0;
	int		error_ret = 0;
	daddr64_t blkno;
	int isize;
	int pg_index;
	int base_index;
	upl_offset_t offset;
	upl_page_info_t *pl;
	vfs_context_t ctx = vfs_context_current();	/* pager context */

	isize = (int)size;

	if (isize <= 0) {
	        result    = PAGER_ERROR;
		error_ret = EINVAL;
		goto out;
	}

	if (UBCINFOEXISTS(vp) == 0) {
		result    = PAGER_ERROR;
		error_ret = EINVAL;

		if (upl && !(flags & UPL_NOCOMMIT))
		        ubc_upl_abort_range(upl, upl_offset, size, UPL_ABORT_FREE_ON_EMPTY);
		goto out;
	}
	if ( !(flags & UPL_VNODE_PAGER)) {
		/*
		 * This is a pageout from the default pager,
		 * just go ahead and call vnop_pageout since
		 * it has already sorted out the dirty ranges
		 */
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(MACHDBG_CODE(DBG_MACH_VM, 1)) | DBG_FUNC_START, 
			size, 1, 0, 0, 0);

		if ( (error_ret = VNOP_PAGEOUT(vp, upl, upl_offset, (off_t)f_offset,
					       (size_t)size, flags, ctx)) )
			result = PAGER_ERROR;

		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(MACHDBG_CODE(DBG_MACH_VM, 1)) | DBG_FUNC_END, 
			size, 1, 0, 0, 0);

		goto out;
	}
	if (upl == NULL) {
		int			request_flags;

		if (vp->v_mount->mnt_vtable->vfc_vfsflags & VFC_VFSVNOP_PAGEOUTV2) {
			/*
			 * filesystem has requested the new form of VNOP_PAGEOUT for file
			 * backed objects... we will not grab the UPL befofe calling VNOP_PAGEOUT...
			 * it is the fileystem's responsibility to grab the range we're denoting
			 * via 'f_offset' and 'size' into a UPL... this allows the filesystem to first
			 * take any locks it needs, before effectively locking the pages into a UPL...
			 */
			KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
				(MACHDBG_CODE(DBG_MACH_VM, 1)) | DBG_FUNC_START, 
				size, (int)f_offset, 0, 0, 0);

			if ( (error_ret = VNOP_PAGEOUT(vp, NULL, upl_offset, (off_t)f_offset,
						       size, flags, ctx)) ) {
				result = PAGER_ERROR;
			}
			KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				(MACHDBG_CODE(DBG_MACH_VM, 1)) | DBG_FUNC_END, 
				size, 0, 0, 0, 0);

			goto out;
		}
		if (flags & UPL_MSYNC)
			request_flags = UPL_UBC_MSYNC | UPL_RET_ONLY_DIRTY;
		else
			request_flags = UPL_UBC_PAGEOUT | UPL_RET_ONLY_DIRTY;
		
	        if (ubc_create_upl_kernel(vp, f_offset, size, &upl, &pl, request_flags, VM_KERN_MEMORY_FILE) != KERN_SUCCESS) {
			result    = PAGER_ERROR;
			error_ret = EINVAL;
			goto out;
		}
		upl_offset = 0;
	} else 
		pl = ubc_upl_pageinfo(upl);

	/*
	 * Ignore any non-present pages at the end of the
	 * UPL so that we aren't looking at a upl that 
	 * may already have been freed by the preceeding
	 * aborts/completions.
	 */
	base_index = upl_offset / PAGE_SIZE;

	for (pg_index = (upl_offset + isize) / PAGE_SIZE; pg_index > base_index;) {
	        if (upl_page_present(pl, --pg_index))
		        break;
		if (pg_index == base_index) {
		        /*
			 * no pages were returned, so release
			 * our hold on the upl and leave
			 */
		        if ( !(flags & UPL_NOCOMMIT))
			        ubc_upl_abort_range(upl, upl_offset, isize, UPL_ABORT_FREE_ON_EMPTY);

			goto out;
		}
	}
	isize = ((pg_index + 1) - base_index) * PAGE_SIZE;

	/*
	 * we come here for pageouts to 'real' files and
	 * for msyncs...  the upl may not contain any
	 * dirty pages.. it's our responsibility to sort
	 * through it and find the 'runs' of dirty pages
	 * to call VNOP_PAGEOUT on...
	 */

	if (ubc_getsize(vp) == 0) {
	        /*
		 * if the file has been effectively deleted, then
		 * we need to go through the UPL and invalidate any
		 * buffer headers we might have that reference any
		 * of it's pages
		 */
		for (offset = upl_offset; isize; isize -= PAGE_SIZE, offset += PAGE_SIZE) {
#if NFSCLIENT
			if (vp->v_tag == VT_NFS)
				/* check with nfs if page is OK to drop */
				error = nfs_buf_page_inval(vp, (off_t)f_offset);
			else
#endif
			{
			        blkno = ubc_offtoblk(vp, (off_t)f_offset);
			        error = buf_invalblkno(vp, blkno, 0);
			}
			if (error) {
			        if ( !(flags & UPL_NOCOMMIT))
				        ubc_upl_abort_range(upl, offset, PAGE_SIZE, UPL_ABORT_FREE_ON_EMPTY);
				if (error_ret == 0)
				        error_ret = error;
				result = PAGER_ERROR;

			} else if ( !(flags & UPL_NOCOMMIT)) {
			        ubc_upl_commit_range(upl, offset, PAGE_SIZE, UPL_COMMIT_FREE_ON_EMPTY);
			}
			f_offset += PAGE_SIZE;
		}
		goto out;
	}

	offset = upl_offset;
	pg_index = base_index;

	while (isize) {
		int  xsize;
		int  num_of_pages;

		if ( !upl_page_present(pl, pg_index)) {
		        /*
			 * we asked for RET_ONLY_DIRTY, so it's possible
			 * to get back empty slots in the UPL
			 * just skip over them
			 */
		        f_offset += PAGE_SIZE;
			offset   += PAGE_SIZE;
			isize    -= PAGE_SIZE;
			pg_index++;

			continue;
		}
		if ( !upl_dirty_page(pl, pg_index)) {
			/*
			 * if the page is not dirty and reached here it is
			 * marked precious or it is due to invalidation in
			 * memory_object_lock request as part of truncation
			 * We also get here from vm_object_terminate()
			 * So all you need to do in these
			 * cases is to invalidate incore buffer if it is there
			 * Note we must not sleep here if the buffer is busy - that is
			 * a lock inversion which causes deadlock.
			 */
#if NFSCLIENT
			if (vp->v_tag == VT_NFS)
				/* check with nfs if page is OK to drop */
				error = nfs_buf_page_inval(vp, (off_t)f_offset);
			else
#endif
			{
			        blkno = ubc_offtoblk(vp, (off_t)f_offset);
			        error = buf_invalblkno(vp, blkno, 0);
			}
			if (error) {
			        if ( !(flags & UPL_NOCOMMIT))
				        ubc_upl_abort_range(upl, offset, PAGE_SIZE, UPL_ABORT_FREE_ON_EMPTY);
				if (error_ret == 0)
				        error_ret = error;
				result = PAGER_ERROR;

			} else if ( !(flags & UPL_NOCOMMIT)) {
			        ubc_upl_commit_range(upl, offset, PAGE_SIZE, UPL_COMMIT_FREE_ON_EMPTY);
			}
		        f_offset += PAGE_SIZE;
			offset   += PAGE_SIZE;
			isize    -= PAGE_SIZE;
			pg_index++;

			continue;
		}
		num_of_pages = 1;
		xsize = isize - PAGE_SIZE;

		while (xsize) {
			if ( !upl_dirty_page(pl, pg_index + num_of_pages))
				break;
			num_of_pages++;
			xsize -= PAGE_SIZE;
		}
		xsize = num_of_pages * PAGE_SIZE;

		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(MACHDBG_CODE(DBG_MACH_VM, 1)) | DBG_FUNC_START, 
			xsize, (int)f_offset, 0, 0, 0);

		if ( (error = VNOP_PAGEOUT(vp, upl, offset, (off_t)f_offset,
					   xsize, flags, ctx)) ) {
		        if (error_ret == 0)
		                error_ret = error;
			result = PAGER_ERROR;
		}
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(MACHDBG_CODE(DBG_MACH_VM, 1)) | DBG_FUNC_END, 
			xsize, 0, 0, 0, 0);

	        f_offset += xsize;
		offset   += xsize;
		isize    -= xsize;
		pg_index += num_of_pages;
	}
out:
	if (errorp)
		*errorp = error_ret;

	return (result);
}