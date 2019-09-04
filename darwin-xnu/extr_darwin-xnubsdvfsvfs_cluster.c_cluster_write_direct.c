#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  user_size_t ;
typedef  int user_addr_t ;
typedef  int /*<<< orphan*/ * upl_t ;
typedef  int upl_size_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int upl_control_flags_t ;
typedef  int u_int32_t ;
struct uio {int uio_iovcnt; scalar_t__ uio_offset; int /*<<< orphan*/  uio_segflg; } ;
struct clios {int io_error; int /*<<< orphan*/  io_mtxp; scalar_t__ io_wanted; scalar_t__ io_issued; scalar_t__ io_completed; } ;
typedef  scalar_t__ off_t ;
typedef  int mach_msg_type_number_t ;
typedef  int kern_return_t ;
typedef  int /*<<< orphan*/  buf_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {int mnt_minsaturationbytecount; scalar_t__ mnt_devblocksize; scalar_t__ mnt_alignmentmask; } ;
struct TYPE_12__ {TYPE_3__* v_mount; } ;

/* Variables and functions */
 int CL_ASYNC ; 
 int CL_COMMIT ; 
 int CL_DIRECT_IO ; 
 int CL_ENCRYPTED ; 
 int CL_NOCACHE ; 
 int CL_PASSIVE ; 
 int CL_PRESERVE ; 
 int CL_THROTTLE ; 
 int /*<<< orphan*/  CL_WRITE ; 
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_NONE ; 
 int DBG_FUNC_START ; 
 int EAGAIN ; 
 scalar_t__ FALSE ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int IO_DIRECT ; 
 int IO_NOCACHE ; 
 int IO_PASSIVE ; 
 int IO_RETURN_ON_THROTTLE ; 
 int IO_SCALE (TYPE_1__*,int) ; 
 int IO_SKIP_ENCRYPTION ; 
 int IO_UNKNOWN ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int KERN_SUCCESS ; 
 int MAX_VECTOR_UPL_ELEMENTS ; 
 int MAX_VECTOR_UPL_SIZE ; 
 int /*<<< orphan*/  MIN_DIRECT_WRITE_SIZE ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PUSH_SYNC ; 
 int /*<<< orphan*/  TASK_WRITE_IMMEDIATE ; 
 int THROTTLE_MAX_IOSIZE ; 
 int THROTTLE_NOW ; 
 scalar_t__ TRUE ; 
 scalar_t__ UIO_SEG_IS_USER_SPACE (int /*<<< orphan*/ ) ; 
 int UPL_CLEAN_IN_PLACE ; 
 int UPL_COPYOUT_FROM ; 
 int UPL_FILE_IO ; 
 int /*<<< orphan*/ * UPL_GET_INTERNAL_PAGE_LIST (int /*<<< orphan*/ *) ; 
 int UPL_NO_SYNC ; 
 int UPL_SET_INTERNAL ; 
 int UPL_SET_IO_WIRE ; 
 int UPL_SET_LITE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int /*<<< orphan*/  cl_mtx_attr ; 
 int /*<<< orphan*/  cl_mtx_grp ; 
 int cluster_io (TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__,int,int,int /*<<< orphan*/ ,struct clios*,int (*) (buf_t,void*),void*) ; 
 int cluster_io_type (struct uio*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_iostate_wait (struct clios*,int,char*) ; 
 int cluster_is_throttled (TYPE_1__*) ; 
 int cluster_max_io_size (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_syncup (TYPE_1__*,scalar_t__,int (*) (buf_t,void*),void*,int /*<<< orphan*/ ) ; 
 int cluster_write_copy (TYPE_1__*,struct uio*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int (*) (buf_t,void*),void*) ; 
 int /*<<< orphan*/  current_map () ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_vector_run_state () ; 
 int /*<<< orphan*/  task_update_logical_writes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  throttle_info_update_by_mount (TYPE_3__*) ; 
 int /*<<< orphan*/  ubc_upl_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uio_curriovbase (struct uio*) ; 
 int /*<<< orphan*/  uio_update (struct uio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_valid_page (int /*<<< orphan*/ *,int) ; 
 int vector_cluster_io (TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__,int,int,int /*<<< orphan*/ ,struct clios*,int (*) (buf_t,void*),void*) ; 
 int /*<<< orphan*/ * vector_upl_create (int) ; 
 int /*<<< orphan*/  vector_upl_set_iostate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vector_upl_set_subupl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int vm_map_get_upl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cluster_write_direct(vnode_t vp, struct uio *uio, off_t oldEOF, off_t newEOF, int *write_type, u_int32_t *write_length,
		     int flags, int (*callback)(buf_t, void *), void *callback_arg)
{
	upl_t            upl;
	upl_page_info_t  *pl;
	vm_offset_t      upl_offset;
	vm_offset_t	 vector_upl_offset = 0;
	u_int32_t	 io_req_size;
	u_int32_t	 offset_in_file;
	u_int32_t	 offset_in_iovbase;
	u_int32_t        io_size;
	int              io_flag = 0;
	upl_size_t	 upl_size, vector_upl_size = 0;
	vm_size_t	 upl_needed_size;
	mach_msg_type_number_t	pages_in_pl;
	upl_control_flags_t upl_flags;
	kern_return_t    kret;
	mach_msg_type_number_t	i;
	int              force_data_sync;
	int              retval = 0;
	int		 first_IO = 1;
	struct clios     iostate;
	user_addr_t	 iov_base;
	u_int32_t	 mem_alignment_mask;
	u_int32_t	 devblocksize;
	u_int32_t	 max_io_size;
	u_int32_t	 max_upl_size;
	u_int32_t        max_vector_size;
	u_int32_t	 bytes_outstanding_limit;
	boolean_t	 io_throttled = FALSE;

	u_int32_t	 vector_upl_iosize = 0;
 	int		 issueVectorUPL = 0,useVectorUPL = (uio->uio_iovcnt > 1);
 	off_t		 v_upl_uio_offset = 0;
 	int		 vector_upl_index=0;
 	upl_t		 vector_upl = NULL;


	/*
	 * When we enter this routine, we know
	 *  -- the resid will not exceed iov_len
	 */
	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 75)) | DBG_FUNC_START,
		     (int)uio->uio_offset, *write_length, (int)newEOF, 0, 0);

	max_upl_size = cluster_max_io_size(vp->v_mount, CL_WRITE);

	io_flag = CL_ASYNC | CL_PRESERVE | CL_COMMIT | CL_THROTTLE | CL_DIRECT_IO;

	if (flags & IO_PASSIVE)
		io_flag |= CL_PASSIVE;
	
	if (flags & IO_NOCACHE)
		io_flag |= CL_NOCACHE;
	
	if (flags & IO_SKIP_ENCRYPTION)
		io_flag |= CL_ENCRYPTED;

	iostate.io_completed = 0;
	iostate.io_issued = 0;
	iostate.io_error = 0;
	iostate.io_wanted = 0;

	lck_mtx_init(&iostate.io_mtxp, cl_mtx_grp, cl_mtx_attr);

	mem_alignment_mask = (u_int32_t)vp->v_mount->mnt_alignmentmask;
	devblocksize = (u_int32_t)vp->v_mount->mnt_devblocksize;

	if (devblocksize == 1) {
               /*
                * the AFP client advertises a devblocksize of 1
                * however, its BLOCKMAP routine maps to physical
                * blocks that are PAGE_SIZE in size...
                * therefore we can't ask for I/Os that aren't page aligned
                * or aren't multiples of PAGE_SIZE in size
                * by setting devblocksize to PAGE_SIZE, we re-instate
                * the old behavior we had before the mem_alignment_mask
                * changes went in...
                */
               devblocksize = PAGE_SIZE;
	}

next_dwrite:
	io_req_size = *write_length;
	iov_base = uio_curriovbase(uio);

	offset_in_file = (u_int32_t)uio->uio_offset & PAGE_MASK;
	offset_in_iovbase = (u_int32_t)iov_base & mem_alignment_mask;

	if (offset_in_file || offset_in_iovbase) {
	        /*
		 * one of the 2 important offsets is misaligned
		 * so fire an I/O through the cache for this entire vector
		 */
	        goto wait_for_dwrites;
	}
	if (iov_base & (devblocksize - 1)) {
	        /*
		 * the offset in memory must be on a device block boundary
		 * so that we can guarantee that we can generate an
		 * I/O that ends on a page boundary in cluster_io
		 */
	        goto wait_for_dwrites;
        }

	task_update_logical_writes(current_task(), (io_req_size & ~PAGE_MASK), TASK_WRITE_IMMEDIATE, vp);
	while (io_req_size >= PAGE_SIZE && uio->uio_offset < newEOF && retval == 0) {
		int	throttle_type;

		if ( (throttle_type = cluster_is_throttled(vp)) ) {
			/*
			 * we're in the throttle window, at the very least
			 * we want to limit the size of the I/O we're about
			 * to issue
			 */
			if ( (flags & IO_RETURN_ON_THROTTLE) && throttle_type == THROTTLE_NOW) {
				/*
				 * we're in the throttle window and at least 1 I/O
				 * has already been issued by a throttleable thread
				 * in this window, so return with EAGAIN to indicate
				 * to the FS issuing the cluster_write call that it
				 * should now throttle after dropping any locks
				 */
				throttle_info_update_by_mount(vp->v_mount);

				io_throttled = TRUE;
				goto wait_for_dwrites;
			}
			max_vector_size = THROTTLE_MAX_IOSIZE;
			max_io_size = THROTTLE_MAX_IOSIZE;
		} else {
			max_vector_size = MAX_VECTOR_UPL_SIZE;
			max_io_size = max_upl_size;
		}

	        if (first_IO) {
		        cluster_syncup(vp, newEOF, callback, callback_arg, callback ? PUSH_SYNC : 0);
			first_IO = 0;
		}
	        io_size  = io_req_size & ~PAGE_MASK;
		iov_base = uio_curriovbase(uio);

		if (io_size > max_io_size)
		        io_size = max_io_size;

		if(useVectorUPL && (iov_base & PAGE_MASK)) {
			/*
			 * We have an iov_base that's not page-aligned.
			 * Issue all I/O's that have been collected within 
			 * this Vectored UPL.
			 */
			if(vector_upl_index) {
				retval = vector_cluster_io(vp, vector_upl, vector_upl_offset, v_upl_uio_offset, vector_upl_iosize, io_flag, (buf_t)NULL, &iostate, callback, callback_arg);
				reset_vector_run_state();
			}
			
		       /*
			* After this point, if we are using the Vector UPL path and the base is
			* not page-aligned then the UPL with that base will be the first in the vector UPL.
			*/
		}

		upl_offset = (vm_offset_t)((u_int32_t)iov_base & PAGE_MASK);
		upl_needed_size = (upl_offset + io_size + (PAGE_SIZE -1)) & ~PAGE_MASK;

		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 76)) | DBG_FUNC_START,
			     (int)upl_offset, upl_needed_size, (int)iov_base, io_size, 0);

		vm_map_t map = UIO_SEG_IS_USER_SPACE(uio->uio_segflg) ? current_map() : kernel_map;
		for (force_data_sync = 0; force_data_sync < 3; force_data_sync++) {
		        pages_in_pl = 0;
			upl_size = upl_needed_size;
			upl_flags = UPL_FILE_IO | UPL_COPYOUT_FROM | UPL_NO_SYNC |
		                    UPL_CLEAN_IN_PLACE | UPL_SET_INTERNAL | UPL_SET_LITE | UPL_SET_IO_WIRE;

			kret = vm_map_get_upl(map,
					      (vm_map_offset_t)(iov_base & ~((user_addr_t)PAGE_MASK)),
					      &upl_size,
					      &upl, 
					      NULL, 
					      &pages_in_pl,
					      &upl_flags,
					      VM_KERN_MEMORY_FILE,
					      force_data_sync);

			if (kret != KERN_SUCCESS) {
			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 76)) | DBG_FUNC_END,
					     0, 0, 0, kret, 0);
				/*
				 * failed to get pagelist
				 *
				 * we may have already spun some portion of this request
				 * off as async requests... we need to wait for the I/O
				 * to complete before returning
				 */
				goto wait_for_dwrites;
			}
			pl = UPL_GET_INTERNAL_PAGE_LIST(upl);
			pages_in_pl = upl_size / PAGE_SIZE;

			for (i = 0; i < pages_in_pl; i++) {
			        if (!upl_valid_page(pl, i))
				        break;		  
			}
			if (i == pages_in_pl)
			        break;

			/*
			 * didn't get all the pages back that we
			 * needed... release this upl and try again
			 */
			ubc_upl_abort(upl, 0);
		}
		if (force_data_sync >= 3) {
		        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 76)) | DBG_FUNC_END,
				     i, pages_in_pl, upl_size, kret, 0);
			/*
			 * for some reason, we couldn't acquire a hold on all
			 * the pages needed in the user's address space
			 *
			 * we may have already spun some portion of this request
			 * off as async requests... we need to wait for the I/O
			 * to complete before returning
			 */
			goto wait_for_dwrites;
		}

		/*
		 * Consider the possibility that upl_size wasn't satisfied.
		 */
		if (upl_size < upl_needed_size) {
		        if (upl_size && upl_offset == 0)
			        io_size = upl_size;
			else
			        io_size = 0;
		}
		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 76)) | DBG_FUNC_END,
			     (int)upl_offset, upl_size, (int)iov_base, io_size, 0);		       

		if (io_size == 0) {
		        ubc_upl_abort(upl, 0);
			/*
			 * we may have already spun some portion of this request
			 * off as async requests... we need to wait for the I/O
			 * to complete before returning
			 */
			goto wait_for_dwrites;
		}
		
		if(useVectorUPL) {
			vm_offset_t end_off = ((iov_base + io_size) & PAGE_MASK);
			if(end_off)
				issueVectorUPL = 1;
			/*
			 * After this point, if we are using a vector UPL, then
			 * either all the UPL elements end on a page boundary OR
			 * this UPL is the last element because it does not end
			 * on a page boundary.
			 */
		}

		/*
		 * we want push out these writes asynchronously so that we can overlap
		 * the preparation of the next I/O
		 * if there are already too many outstanding writes
		 * wait until some complete before issuing the next
		 */
		if (vp->v_mount->mnt_minsaturationbytecount)
			bytes_outstanding_limit = vp->v_mount->mnt_minsaturationbytecount;
		else
			bytes_outstanding_limit = max_upl_size * IO_SCALE(vp, 2);

		cluster_iostate_wait(&iostate, bytes_outstanding_limit, "cluster_write_direct");

		if (iostate.io_error) {
		        /*
			 * one of the earlier writes we issued ran into a hard error
			 * don't issue any more writes, cleanup the UPL
			 * that was just created but not used, then
			 * go wait for all writes that are part of this stream
			 * to complete before returning the error to the caller
			 */
		        ubc_upl_abort(upl, 0);

		        goto wait_for_dwrites;
	        }

		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 77)) | DBG_FUNC_START,
			     (int)upl_offset, (int)uio->uio_offset, io_size, io_flag, 0);

		if(!useVectorUPL)
			retval = cluster_io(vp, upl, upl_offset, uio->uio_offset,
				   io_size, io_flag, (buf_t)NULL, &iostate, callback, callback_arg);

		else {
			if(!vector_upl_index) {
				vector_upl = vector_upl_create(upl_offset);
				v_upl_uio_offset = uio->uio_offset;
				vector_upl_offset = upl_offset;
			}

			vector_upl_set_subupl(vector_upl,upl,upl_size);
			vector_upl_set_iostate(vector_upl, upl, vector_upl_size, upl_size);
			vector_upl_index++;
			vector_upl_iosize += io_size;
			vector_upl_size += upl_size;

			if(issueVectorUPL || vector_upl_index ==  MAX_VECTOR_UPL_ELEMENTS || vector_upl_size >= max_vector_size) {
				retval = vector_cluster_io(vp, vector_upl, vector_upl_offset, v_upl_uio_offset, vector_upl_iosize, io_flag, (buf_t)NULL, &iostate, callback, callback_arg);
				reset_vector_run_state();
			}
		}	

		/*
		 * update the uio structure to
		 * reflect the I/O that we just issued
		 */
		uio_update(uio, (user_size_t)io_size);

		/*
		 * in case we end up calling through to cluster_write_copy to finish
		 * the tail of this request, we need to update the oldEOF so that we
		 * don't zero-fill the head of a page if we've successfully written
		 * data to that area... 'cluster_write_copy' will zero-fill the head of a
		 * page that is beyond the oldEOF if the write is unaligned... we only
		 * want that to happen for the very first page of the cluster_write, 
		 * NOT the first page of each vector making up a multi-vector write.
		 */
		if (uio->uio_offset > oldEOF)
			oldEOF = uio->uio_offset;

		io_req_size -= io_size;

		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 77)) | DBG_FUNC_END,
			     (int)upl_offset, (int)uio->uio_offset, io_req_size, retval, 0);

	} /* end while */

        if (retval == 0 && iostate.io_error == 0 && io_req_size == 0) {

	        retval = cluster_io_type(uio, write_type, write_length, MIN_DIRECT_WRITE_SIZE);

		if (retval == 0 && *write_type == IO_DIRECT) {

		        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 75)) | DBG_FUNC_NONE,
				     (int)uio->uio_offset, *write_length, (int)newEOF, 0, 0);

		        goto next_dwrite;
		}
        }

wait_for_dwrites:

	if (retval == 0 && iostate.io_error == 0 && useVectorUPL && vector_upl_index) {
		retval = vector_cluster_io(vp, vector_upl, vector_upl_offset, v_upl_uio_offset, vector_upl_iosize, io_flag, (buf_t)NULL, &iostate, callback, callback_arg);
		reset_vector_run_state();	
	}
	/*
	 * make sure all async writes issued as part of this stream
	 * have completed before we return
	 */
	cluster_iostate_wait(&iostate, 0, "cluster_write_direct");

	if (iostate.io_error)
	        retval = iostate.io_error;

	lck_mtx_destroy(&iostate.io_mtxp, cl_mtx_grp);

	if (io_throttled == TRUE && retval == 0)
		retval = EAGAIN;

	if (io_req_size && retval == 0) {
	        /*
		 * we couldn't handle the tail of this request in DIRECT mode
		 * so fire it through the copy path
		 *
		 * note that flags will never have IO_HEADZEROFILL or IO_TAILZEROFILL set
		 * so we can just pass 0 in for the headOff and tailOff
		 */
		if (uio->uio_offset > oldEOF)
			oldEOF = uio->uio_offset;

	        retval = cluster_write_copy(vp, uio, io_req_size, oldEOF, newEOF, (off_t)0, (off_t)0, flags, callback, callback_arg);

		*write_type = IO_UNKNOWN;
	}
	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 75)) | DBG_FUNC_END,
		     (int)uio->uio_offset, io_req_size, retval, 4, 0);

	return (retval);
}