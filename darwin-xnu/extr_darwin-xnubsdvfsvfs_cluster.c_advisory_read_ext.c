#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int vm_offset_t ;
typedef  int upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int uint32_t ;
struct clios {int dummy; } ;
typedef  int off_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  buf_t ;
struct TYPE_7__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int CL_AGE ; 
 int CL_ASYNC ; 
 int CL_COMMIT ; 
 int CL_READ ; 
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EINVAL ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int PAGE_MASK ; 
 int PAGE_MASK_64 ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UBCINFOEXISTS (TYPE_1__*) ; 
 int UPL_RET_ONLY_ABSENT ; 
 int /*<<< orphan*/  UPL_ROP_PRESENT ; 
 int UPL_SET_LITE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int cluster_io (TYPE_1__*,int,int,int,int,int,int /*<<< orphan*/ ,struct clios*,int (*) (buf_t,void*),void*) ; 
 int cluster_max_io_size (int /*<<< orphan*/ ,int) ; 
 scalar_t__ disk_conditioner_mount_is_ssd (int /*<<< orphan*/ ) ; 
 int speculative_prefetch_max_iosize ; 
 scalar_t__ ubc_create_upl_kernel (TYPE_1__*,int,int,int*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_range_op (TYPE_1__*,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ubc_upl_abort (int,int /*<<< orphan*/ ) ; 
 scalar_t__ upl_page_present (int /*<<< orphan*/ *,int) ; 

int
advisory_read_ext(vnode_t vp, off_t filesize, off_t f_offset, int resid, int (*callback)(buf_t, void *), void *callback_arg, int bflag)
{
	upl_page_info_t *pl;
	upl_t            upl;
	vm_offset_t      upl_offset;
	int	         upl_size;
	off_t 	         upl_f_offset;
	int		 start_offset;
	int	         start_pg;
	int		 last_pg;
	int              pages_in_upl;
	off_t            max_size;
	int              io_size;
	kern_return_t    kret;
	int              retval = 0;
	int              issued_io;
	int              skip_range;
	uint32_t	 max_io_size;


	if ( !UBCINFOEXISTS(vp))
		return(EINVAL);

	if (resid < 0)
		return(EINVAL);

	max_io_size = cluster_max_io_size(vp->v_mount, CL_READ);

#if CONFIG_EMBEDDED
	if (max_io_size > speculative_prefetch_max_iosize)
		max_io_size = speculative_prefetch_max_iosize;
#else
	if (disk_conditioner_mount_is_ssd(vp->v_mount)) {
		if (max_io_size > speculative_prefetch_max_iosize)
			max_io_size = speculative_prefetch_max_iosize;
	}
#endif

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 60)) | DBG_FUNC_START,
		     (int)f_offset, resid, (int)filesize, 0, 0);

	while (resid && f_offset < filesize && retval == 0) {
		/*
		 * compute the size of the upl needed to encompass
		 * the requested read... limit each call to cluster_io
		 * to the maximum UPL size... cluster_io will clip if
		 * this exceeds the maximum io_size for the device,
		 * make sure to account for 
		 * a starting offset that's not page aligned
		 */
		start_offset = (int)(f_offset & PAGE_MASK_64);
		upl_f_offset = f_offset - (off_t)start_offset;
		max_size     = filesize - f_offset;

		if (resid < max_size)
		        io_size = resid;
		else
		        io_size = max_size;

		upl_size = (start_offset + io_size + (PAGE_SIZE - 1)) & ~PAGE_MASK;
	        if ((uint32_t)upl_size > max_io_size)
		        upl_size = max_io_size;

		skip_range = 0;
		/*
		 * return the number of contiguously present pages in the cache
		 * starting at upl_f_offset within the file
		 */
		ubc_range_op(vp, upl_f_offset, upl_f_offset + upl_size, UPL_ROP_PRESENT, &skip_range);

		if (skip_range) {
		        /*
			 * skip over pages already present in the cache
			 */
		        io_size = skip_range - start_offset;

		        f_offset += io_size;
			resid    -= io_size;

			if (skip_range == upl_size)
			        continue;
			/*
			 * have to issue some real I/O
			 * at this point, we know it's starting on a page boundary
			 * because we've skipped over at least the first page in the request
			 */
			start_offset = 0;
			upl_f_offset += skip_range;
			upl_size     -= skip_range;
		}
		pages_in_upl = upl_size / PAGE_SIZE;

		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 61)) | DBG_FUNC_START,
			     upl, (int)upl_f_offset, upl_size, start_offset, 0);

		kret = ubc_create_upl_kernel(vp,
				      upl_f_offset,
				      upl_size,
				      &upl,
				      &pl,
				      UPL_RET_ONLY_ABSENT | UPL_SET_LITE,
				      VM_KERN_MEMORY_FILE);
		if (kret != KERN_SUCCESS)
		        return(retval);
		issued_io = 0;

		/*
		 * before we start marching forward, we must make sure we end on 
		 * a present page, otherwise we will be working with a freed
		 * upl
		 */
		for (last_pg = pages_in_upl - 1; last_pg >= 0; last_pg--) {
		        if (upl_page_present(pl, last_pg))
			        break;
		}
		pages_in_upl = last_pg + 1;


		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 61)) | DBG_FUNC_END,
			     upl, (int)upl_f_offset, upl_size, start_offset, 0);


		for (last_pg = 0; last_pg < pages_in_upl; ) {
		        /*
			 * scan from the beginning of the upl looking for the first
			 * page that is present.... this will become the first page in
			 * the request we're going to make to 'cluster_io'... if all
			 * of the pages are absent, we won't call through to 'cluster_io'
			 */
		        for (start_pg = last_pg; start_pg < pages_in_upl; start_pg++) {
			        if (upl_page_present(pl, start_pg))
				        break;
			}

			/*
			 * scan from the starting present page looking for an absent
			 * page before the end of the upl is reached, if we 
			 * find one, then it will terminate the range of pages being
			 * presented to 'cluster_io'
			 */
			for (last_pg = start_pg; last_pg < pages_in_upl; last_pg++) {
			        if (!upl_page_present(pl, last_pg))
				        break;
			}

			if (last_pg > start_pg) {		
			        /*
				 * we found a range of pages that must be filled
				 * if the last page in this range is the last page of the file
				 * we may have to clip the size of it to keep from reading past
				 * the end of the last physical block associated with the file
				 */
			        upl_offset = start_pg * PAGE_SIZE;
				io_size    = (last_pg - start_pg) * PAGE_SIZE;

				if ((off_t)(upl_f_offset + upl_offset + io_size) > filesize)
				        io_size = filesize - (upl_f_offset + upl_offset);

				/*
				 * issue an asynchronous read to cluster_io
				 */
				retval = cluster_io(vp, upl, upl_offset, upl_f_offset + upl_offset, io_size,
						    CL_ASYNC | CL_READ | CL_COMMIT | CL_AGE | bflag, (buf_t)NULL, (struct clios *)NULL, callback, callback_arg);

				issued_io = 1;
			}
		}
		if (issued_io == 0)
		        ubc_upl_abort(upl, 0);

		io_size = upl_size - start_offset;
		
		if (io_size > resid)
		        io_size = resid;
		f_offset += io_size;
		resid    -= io_size;
	}

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 60)) | DBG_FUNC_END,
		     (int)f_offset, resid, retval, 0, 0);

	return(retval);
}