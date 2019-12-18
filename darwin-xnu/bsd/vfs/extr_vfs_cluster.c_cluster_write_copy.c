#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  long long vm_size_t ;
typedef  int vm_offset_t ;
typedef  int upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int u_int32_t ;
typedef  long long u_int ;
struct uio {scalar_t__ uio_offset; int uio_flags; } ;
struct clios {int dummy; } ;
struct cl_extent {void* e_addr; void* b_addr; } ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ kern_return_t ;
typedef  void* daddr64_t ;
typedef  int /*<<< orphan*/  buf_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int CL_ENCRYPTED ; 
 int CL_NOCACHE ; 
 int CL_PASSIVE ; 
 int CL_READ ; 
 int /*<<< orphan*/  CL_WRITE ; 
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_NONE ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  FALSE ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int IO_HEADZEROFILL ; 
 int IO_NOCACHE ; 
 int IO_PASSIVE ; 
 int IO_SKIP_ENCRYPTION ; 
 int IO_SYNC ; 
 int IO_TAILZEROFILL ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int MNT_DEFWRITE ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_MASK_64 ; 
 int PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int /*<<< orphan*/  TRUE ; 
 int UIO_FLAGS_IS_COMPRESSED_FILE ; 
 int UPL_ABORT_DUMP_PAGES ; 
 int UPL_ABORT_FREE_ON_EMPTY ; 
 int UPL_COMMIT_FREE_ON_EMPTY ; 
 int UPL_COMMIT_INACTIVATE ; 
 int UPL_COMMIT_SET_DIRTY ; 
 int UPL_SET_LITE ; 
 int UPL_WILL_MODIFY ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 scalar_t__ VT_APFS ; 
 int cluster_copy_ubc_data_internal (TYPE_1__*,struct uio*,int*,int,int) ; 
 int cluster_copy_upl_data (struct uio*,int,int,int*) ; 
 int cluster_io (TYPE_1__*,int,int,scalar_t__,int,int,int /*<<< orphan*/ ,struct clios*,int (*) (buf_t,void*),void*) ; 
 long long cluster_max_io_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cluster_push_now (TYPE_1__*,struct cl_extent*,scalar_t__,int,int (*) (buf_t,void*),void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_update_state_internal (TYPE_1__*,struct cl_extent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int (*) (buf_t,void*),void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_zero (int,int,long long,int /*<<< orphan*/ *) ; 
 int cluster_zero_range (int,int /*<<< orphan*/ *,int,int,scalar_t__,scalar_t__,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ ubc_create_upl_kernel (TYPE_1__*,scalar_t__,long long,int*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_upl_abort_range (int,int,long long,int) ; 
 int /*<<< orphan*/  ubc_upl_commit_range (int,int /*<<< orphan*/ ,long long,int) ; 
 int uio_resid (struct uio*) ; 
 int /*<<< orphan*/  upl_valid_page (int /*<<< orphan*/ *,int) ; 
 int vfs_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_tag (TYPE_1__*) ; 

__attribute__((used)) static int
cluster_write_copy(vnode_t vp, struct uio *uio, u_int32_t io_req_size, off_t oldEOF, off_t newEOF, off_t headOff,
		   off_t tailOff, int flags, int (*callback)(buf_t, void *), void *callback_arg)
{
	upl_page_info_t *pl;
	upl_t            upl;
	vm_offset_t      upl_offset = 0;
	vm_size_t	 upl_size;
	off_t 	         upl_f_offset;
	int              pages_in_upl;
	int		 start_offset;
	int              xfer_resid;
	int              io_size;
	int              io_offset;
	int              bytes_to_zero;
	int              bytes_to_move;
	kern_return_t    kret;
	int              retval = 0;
	int              io_resid;
	long long        total_size;
	long long        zero_cnt;
	off_t            zero_off;
	long long        zero_cnt1;
	off_t            zero_off1;
	off_t		 write_off = 0;
	int		 write_cnt = 0;
	boolean_t	 first_pass = FALSE;
	struct cl_extent cl;
	int              bflag;
	u_int		 max_io_size;

	if (uio) {
	        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 40)) | DBG_FUNC_START,
			     (int)uio->uio_offset, io_req_size, (int)oldEOF, (int)newEOF, 0);

	        io_resid = io_req_size;
	} else {
	        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 40)) | DBG_FUNC_START,
			     0, 0, (int)oldEOF, (int)newEOF, 0);

	        io_resid = 0;
	}
	if (flags & IO_PASSIVE)
		bflag = CL_PASSIVE;
	else
		bflag = 0;
	if (flags & IO_NOCACHE)
		bflag |= CL_NOCACHE;
	
	if (flags & IO_SKIP_ENCRYPTION)
		bflag |= CL_ENCRYPTED;

	zero_cnt  = 0;
	zero_cnt1 = 0;
	zero_off  = 0;
	zero_off1 = 0;

	max_io_size = cluster_max_io_size(vp->v_mount, CL_WRITE);

	if (flags & IO_HEADZEROFILL) {
	        /*
		 * some filesystems (HFS is one) don't support unallocated holes within a file...
		 * so we zero fill the intervening space between the old EOF and the offset
		 * where the next chunk of real data begins.... ftruncate will also use this
		 * routine to zero fill to the new EOF when growing a file... in this case, the
		 * uio structure will not be provided
		 */
	        if (uio) {
		        if (headOff < uio->uio_offset) {
			        zero_cnt = uio->uio_offset - headOff;
				zero_off = headOff;
			}
		} else if (headOff < newEOF) {	
		        zero_cnt = newEOF - headOff;
			zero_off = headOff;
		}
	} else {
		if (uio && uio->uio_offset > oldEOF) {
			zero_off = uio->uio_offset & ~PAGE_MASK_64;

			if (zero_off >= oldEOF) {
				zero_cnt = uio->uio_offset - zero_off;

				flags |= IO_HEADZEROFILL;
			}
		}
	}
	if (flags & IO_TAILZEROFILL) {
	        if (uio) {
		        zero_off1 = uio->uio_offset + io_req_size;

			if (zero_off1 < tailOff)
			        zero_cnt1 = tailOff - zero_off1;
		}	
	} else {
		if (uio && newEOF > oldEOF) {
		        zero_off1 = uio->uio_offset + io_req_size;

			if (zero_off1 == newEOF && (zero_off1 & PAGE_MASK_64)) {
				zero_cnt1 = PAGE_SIZE_64 - (zero_off1 & PAGE_MASK_64);

				flags |= IO_TAILZEROFILL;
			}
		}
	}
	if (zero_cnt == 0 && uio == (struct uio *) 0) {
	        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 40)) | DBG_FUNC_END,
			     retval, 0, 0, 0, 0);
		return (0);
	}
	if (uio) {
		write_off = uio->uio_offset;
		write_cnt = uio_resid(uio);
		/*
		 * delay updating the sequential write info
		 * in the control block until we've obtained
		 * the lock for it
		 */
		first_pass = TRUE;
	}
	while ((total_size = (io_resid + zero_cnt + zero_cnt1)) && retval == 0) {
	        /*
		 * for this iteration of the loop, figure out where our starting point is
		 */
	        if (zero_cnt) {
		        start_offset = (int)(zero_off & PAGE_MASK_64);
			upl_f_offset = zero_off - start_offset;
		} else if (io_resid) {
		        start_offset = (int)(uio->uio_offset & PAGE_MASK_64);
			upl_f_offset = uio->uio_offset - start_offset;
		} else {
		        start_offset = (int)(zero_off1 & PAGE_MASK_64);
			upl_f_offset = zero_off1 - start_offset;
		}
	        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 46)) | DBG_FUNC_NONE,
			     (int)zero_off, (int)zero_cnt, (int)zero_off1, (int)zero_cnt1, 0);

	        if (total_size > max_io_size)
		        total_size = max_io_size;

		cl.b_addr = (daddr64_t)(upl_f_offset / PAGE_SIZE_64);
		
		if (uio && ((flags & (IO_SYNC | IO_HEADZEROFILL | IO_TAILZEROFILL)) == 0)) {
		        /*
			 * assumption... total_size <= io_resid
			 * because IO_HEADZEROFILL and IO_TAILZEROFILL not set
			 */
		        if ((start_offset + total_size) > max_io_size)
			        total_size = max_io_size - start_offset;
		        xfer_resid = total_size;

		        retval = cluster_copy_ubc_data_internal(vp, uio, &xfer_resid, 1, 1);

			if (retval)
			        break;

			io_resid    -= (total_size - xfer_resid);
			total_size   = xfer_resid;
			start_offset = (int)(uio->uio_offset & PAGE_MASK_64);
			upl_f_offset = uio->uio_offset - start_offset;

			if (total_size == 0) {
			        if (start_offset) {
				        /*
					 * the write did not finish on a page boundary
					 * which will leave upl_f_offset pointing to the
					 * beginning of the last page written instead of
					 * the page beyond it... bump it in this case
					 * so that the cluster code records the last page
					 * written as dirty
					 */
				        upl_f_offset += PAGE_SIZE_64;
				}
			        upl_size = 0;
				
			        goto check_cluster;
			}
		}
		/*
		 * compute the size of the upl needed to encompass
		 * the requested write... limit each call to cluster_io
		 * to the maximum UPL size... cluster_io will clip if
		 * this exceeds the maximum io_size for the device,
		 * make sure to account for 
		 * a starting offset that's not page aligned
		 */
		upl_size = (start_offset + total_size + (PAGE_SIZE - 1)) & ~PAGE_MASK;

	        if (upl_size > max_io_size)
		        upl_size = max_io_size;

		pages_in_upl = upl_size / PAGE_SIZE;
		io_size      = upl_size - start_offset;
		
		if ((long long)io_size > total_size)
		        io_size = total_size;

		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 41)) | DBG_FUNC_START, upl_size, io_size, total_size, 0, 0);
			

		/*
		 * Gather the pages from the buffer cache.
		 * The UPL_WILL_MODIFY flag lets the UPL subsystem know
		 * that we intend to modify these pages.
		 */
		kret = ubc_create_upl_kernel(vp,
				      upl_f_offset,
				      upl_size,
				      &upl,
				      &pl,
				      UPL_SET_LITE | (( uio!=NULL && (uio->uio_flags & UIO_FLAGS_IS_COMPRESSED_FILE)) ? 0 : UPL_WILL_MODIFY),
				      VM_KERN_MEMORY_FILE);
		if (kret != KERN_SUCCESS)
			panic("cluster_write_copy: failed to get pagelist");

		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 41)) | DBG_FUNC_END,
			upl, (int)upl_f_offset, start_offset, 0, 0);

		if (start_offset && upl_f_offset < oldEOF && !upl_valid_page(pl, 0)) {
			int   read_size;

			/*
			 * we're starting in the middle of the first page of the upl
			 * and the page isn't currently valid, so we're going to have
			 * to read it in first... this is a synchronous operation
			 */
			read_size = PAGE_SIZE;

			if ((upl_f_offset + read_size) > oldEOF)
			        read_size = oldEOF - upl_f_offset;

		        retval = cluster_io(vp, upl, 0, upl_f_offset, read_size,
					    CL_READ | bflag, (buf_t)NULL, (struct clios *)NULL, callback, callback_arg);
			if (retval) {
				/*
				 * we had an error during the read which causes us to abort
				 * the current cluster_write request... before we do, we need
				 * to release the rest of the pages in the upl without modifying
				 * there state and mark the failed page in error
				 */
				ubc_upl_abort_range(upl, 0, PAGE_SIZE, UPL_ABORT_DUMP_PAGES|UPL_ABORT_FREE_ON_EMPTY);

				if (upl_size > PAGE_SIZE)
				        ubc_upl_abort_range(upl, 0, upl_size, UPL_ABORT_FREE_ON_EMPTY);

				KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 45)) | DBG_FUNC_NONE,
					     upl, 0, 0, retval, 0);
				break;
			}
		}
		if ((start_offset == 0 || upl_size > PAGE_SIZE) && ((start_offset + io_size) & PAGE_MASK)) {
		        /* 
			 * the last offset we're writing to in this upl does not end on a page
			 * boundary... if it's not beyond the old EOF, then we'll also need to
			 * pre-read this page in if it isn't already valid
			 */
		        upl_offset = upl_size - PAGE_SIZE;

		        if ((upl_f_offset + start_offset + io_size) < oldEOF &&
			    !upl_valid_page(pl, upl_offset / PAGE_SIZE)) {
			        int   read_size;

				read_size = PAGE_SIZE;

				if ((off_t)(upl_f_offset + upl_offset + read_size) > oldEOF)
				        read_size = oldEOF - (upl_f_offset + upl_offset);

			        retval = cluster_io(vp, upl, upl_offset, upl_f_offset + upl_offset, read_size,
						    CL_READ | bflag, (buf_t)NULL, (struct clios *)NULL, callback, callback_arg);
				if (retval) {
					/*
					 * we had an error during the read which causes us to abort
					 * the current cluster_write request... before we do, we
					 * need to release the rest of the pages in the upl without
					 * modifying there state and mark the failed page in error
					 */
					ubc_upl_abort_range(upl, upl_offset, PAGE_SIZE, UPL_ABORT_DUMP_PAGES|UPL_ABORT_FREE_ON_EMPTY);

					if (upl_size > PAGE_SIZE)
					        ubc_upl_abort_range(upl, 0, upl_size, UPL_ABORT_FREE_ON_EMPTY);

					KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 45)) | DBG_FUNC_NONE,
						     upl, 0, 0, retval, 0);
					break;
				}
			}
		}
		xfer_resid = io_size;
		io_offset = start_offset;

		while (zero_cnt && xfer_resid) {

		        if (zero_cnt < (long long)xfer_resid)
			        bytes_to_zero = zero_cnt;
			else
			        bytes_to_zero = xfer_resid;

			bytes_to_zero = cluster_zero_range(upl, pl, flags, io_offset, zero_off, upl_f_offset, bytes_to_zero);

			xfer_resid -= bytes_to_zero;
			zero_cnt   -= bytes_to_zero;
			zero_off   += bytes_to_zero;
			io_offset  += bytes_to_zero;
		}
		if (xfer_resid && io_resid) {
		        u_int32_t  io_requested;

			bytes_to_move = min(io_resid, xfer_resid);
			io_requested = bytes_to_move;

			retval = cluster_copy_upl_data(uio, upl, io_offset, (int *)&io_requested);

			if (retval) {
				ubc_upl_abort_range(upl, 0, upl_size, UPL_ABORT_FREE_ON_EMPTY);

				KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 45)) | DBG_FUNC_NONE,
					     upl, 0, 0, retval, 0);
			} else {
			        io_resid   -= bytes_to_move;
				xfer_resid -= bytes_to_move;
				io_offset  += bytes_to_move;
			}
		}
		while (xfer_resid && zero_cnt1 && retval == 0) {

		        if (zero_cnt1 < (long long)xfer_resid)
			        bytes_to_zero = zero_cnt1;
			else
			        bytes_to_zero = xfer_resid;

			bytes_to_zero = cluster_zero_range(upl, pl, flags, io_offset, zero_off1, upl_f_offset, bytes_to_zero);

			xfer_resid -= bytes_to_zero;
			zero_cnt1  -= bytes_to_zero;
			zero_off1  += bytes_to_zero;
			io_offset  += bytes_to_zero;
		}
		if (retval == 0) {
			int do_zeroing = 1;
			
			io_size += start_offset;

			/* Force more restrictive zeroing behavior only on APFS */
			if ((vnode_tag(vp) == VT_APFS) && (newEOF < oldEOF)) {
				do_zeroing = 0;
			}

			if (do_zeroing && (upl_f_offset + io_size) >= newEOF && (u_int)io_size < upl_size) {

				/*
				 * if we're extending the file with this write
				 * we'll zero fill the rest of the page so that
				 * if the file gets extended again in such a way as to leave a
				 * hole starting at this EOF, we'll have zero's in the correct spot
				 */
				cluster_zero(upl, io_size, upl_size - io_size, NULL); 
			}
			/*
			 * release the upl now if we hold one since...
			 * 1) pages in it may be present in the sparse cluster map
			 *    and may span 2 separate buckets there... if they do and 
			 *    we happen to have to flush a bucket to make room and it intersects
			 *    this upl, a deadlock may result on page BUSY
			 * 2) we're delaying the I/O... from this point forward we're just updating
			 *    the cluster state... no need to hold the pages, so commit them
			 * 3) IO_SYNC is set...
			 *    because we had to ask for a UPL that provides currenty non-present pages, the
			 *    UPL has been automatically set to clear the dirty flags (both software and hardware)
			 *    upon committing it... this is not the behavior we want since it's possible for
			 *    pages currently present as part of a mapped file to be dirtied while the I/O is in flight.
			 *    we'll pick these pages back up later with the correct behavior specified.
			 * 4) we don't want to hold pages busy in a UPL and then block on the cluster lock... if a flush
			 *    of this vnode is in progress, we will deadlock if the pages being flushed intersect the pages
			 *    we hold since the flushing context is holding the cluster lock.
			 */
			ubc_upl_commit_range(upl, 0, upl_size,
					     UPL_COMMIT_SET_DIRTY | UPL_COMMIT_INACTIVATE | UPL_COMMIT_FREE_ON_EMPTY);
check_cluster:
			/*
			 * calculate the last logical block number 
			 * that this delayed I/O encompassed
			 */
			cl.e_addr = (daddr64_t)((upl_f_offset + (off_t)upl_size) / PAGE_SIZE_64);

			if (flags & IO_SYNC) {
				/*
				 * if the IO_SYNC flag is set than we need to bypass
				 * any clustering and immediately issue the I/O
				 *
				 * we don't hold the lock at this point
				 *
				 * we've already dropped the current upl, so pick it back up with COPYOUT_FROM set
				 * so that we correctly deal with a change in state of the hardware modify bit...
				 * we do this via cluster_push_now... by passing along the IO_SYNC flag, we force
				 * cluster_push_now to wait until all the I/Os have completed... cluster_push_now is also
				 * responsible for generating the correct sized I/O(s)
				 */
			        retval = cluster_push_now(vp, &cl, newEOF, flags, callback, callback_arg, FALSE);
			} else {
				boolean_t defer_writes = FALSE;

				if (vfs_flags(vp->v_mount) & MNT_DEFWRITE)
					defer_writes = TRUE;

				cluster_update_state_internal(vp, &cl, flags, defer_writes, &first_pass,
							      write_off, write_cnt, newEOF, callback, callback_arg, FALSE);
			}
		}
	}
	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 40)) | DBG_FUNC_END, retval, 0, io_resid, 0, 0);

	return (retval);
}