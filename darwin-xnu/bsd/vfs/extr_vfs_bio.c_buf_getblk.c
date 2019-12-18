#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  void* upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct bufhashhdr {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int kern_return_t ;
typedef  int daddr64_t ;
typedef  TYPE_4__* buf_t ;
struct TYPE_29__ {int b_tag; int b_bcount; int b_bufsize; int b_lblkno; int b_blkno; int b_validend; int b_dirtyend; int /*<<< orphan*/ * b_stackgetblk; int /*<<< orphan*/  b_flags; int /*<<< orphan*/  b_datap; int /*<<< orphan*/  b_dirtyoff; int /*<<< orphan*/  b_validoff; void* b_upl; TYPE_3__* b_vp; int /*<<< orphan*/  b_owner; int /*<<< orphan*/  b_lflags; } ;
struct TYPE_28__ {TYPE_2__* v_mount; } ;
struct TYPE_26__ {int /*<<< orphan*/  f_fstypename; } ;
struct TYPE_27__ {TYPE_1__ mnt_vfsstat; } ;
struct TYPE_25__ {int /*<<< orphan*/  bufs_miss; int /*<<< orphan*/  bufs_vmhits; int /*<<< orphan*/  bufs_incore; int /*<<< orphan*/  bufs_busyincore; } ;

/* Variables and functions */
#define  BLK_META 130 
 int BLK_ONLYVALID ; 
#define  BLK_READ 129 
#define  BLK_WRITE 128 
 int BL_BUSY ; 
 int BL_WANTED ; 
 int BQ_EMPTY ; 
 struct bufhashhdr* BUFHASH (TYPE_3__*,int) ; 
 int B_CACHE ; 
 int B_DELWRI ; 
 int B_DONE ; 
 int B_INVAL ; 
 int B_META ; 
 int B_WASDIRTY ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_NONE ; 
 int DBG_FUNC_START ; 
 int EWOULDBLOCK ; 
 int FALSE ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,...) ; 
 int KERN_SUCCESS ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  OSAddAtomicLong (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSBacktrace (int /*<<< orphan*/ *,int) ; 
 int PAGE_SIZE ; 
 int PCATCH ; 
 int PDROP ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int) ; 
 int TRUE ; 
 scalar_t__ UBCINFOEXISTS (TYPE_3__*) ; 
 int UPL_PRECIOUS ; 
 int UPL_WILL_MODIFY ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int VNODE_READ ; 
 int VNODE_WRITE ; 
 int /*<<< orphan*/  VNOP_BLOCKMAP (TYPE_3__*,int /*<<< orphan*/ ,int,int*,size_t*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  allocbuf (TYPE_4__*,int) ; 
 int /*<<< orphan*/  bgetvp_locked (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  binshash (TYPE_4__*,struct bufhashhdr*) ; 
 int /*<<< orphan*/  bremfree_locked (TYPE_4__*) ; 
 int /*<<< orphan*/  buf_brelse (TYPE_4__*) ; 
 int /*<<< orphan*/  buf_busycount ; 
 int /*<<< orphan*/  buf_bwrite (TYPE_4__*) ; 
 int /*<<< orphan*/  buf_mtxp ; 
 TYPE_12__ bufstats ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_4__* getnewbuf (int,int,int*) ; 
 TYPE_4__* incore_locked (TYPE_3__*,int,struct bufhashhdr*) ; 
 struct bufhashhdr invalhash ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int msleep (TYPE_4__*,int /*<<< orphan*/ ,int,char*,struct timespec*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ubc_blktooff (TYPE_3__*,int) ; 
 int ubc_create_upl_kernel (TYPE_3__*,int /*<<< orphan*/ ,int,void**,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int ubc_upl_map (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upl_dirty_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_ubc_alias_set (void*,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  upl_valid_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isreg (TYPE_3__*) ; 

buf_t
buf_getblk(vnode_t vp, daddr64_t blkno, int size, int slpflag, int slptimeo, int operation)
{
	buf_t bp;
	int   err;
	upl_t upl;
	upl_page_info_t *pl;
	kern_return_t kret;
	int ret_only_valid;
	struct timespec ts;
	int upl_flags;
	struct	bufhashhdr *dp;

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 386)) | DBG_FUNC_START,
		     (uintptr_t)(blkno * PAGE_SIZE), size, operation, 0, 0);

	ret_only_valid = operation & BLK_ONLYVALID;
	operation &= ~BLK_ONLYVALID;
	dp = BUFHASH(vp, blkno);
start:
	lck_mtx_lock_spin(buf_mtxp);

	if ((bp = incore_locked(vp, blkno, dp))) {
		/*
		 * Found in the Buffer Cache
		 */
		if (ISSET(bp->b_lflags, BL_BUSY)) {
			/*
			 * but is busy
			 */
			switch (operation) {
			case BLK_READ:
			case BLK_WRITE:
			case BLK_META:
				SET(bp->b_lflags, BL_WANTED);
				bufstats.bufs_busyincore++;

				/*
				 * don't retake the mutex after being awakened...
				 * the time out is in msecs 
				 */
				ts.tv_sec = (slptimeo/1000);
				ts.tv_nsec = (slptimeo % 1000) * 10  * NSEC_PER_USEC * 1000;

				KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 396)) | DBG_FUNC_NONE,
					     (uintptr_t)blkno, size, operation, 0, 0);

				err = msleep(bp, buf_mtxp, slpflag | PDROP | (PRIBIO + 1), "buf_getblk", &ts);

				/*
				 * Callers who call with PCATCH or timeout are
				 * willing to deal with the NULL pointer
				 */
				if (err && ((slpflag & PCATCH) || ((err == EWOULDBLOCK) && slptimeo)))
					return (NULL);
				goto start;
				/*NOTREACHED*/

			default:
			        /*
				 * unknown operation requested
				 */
				panic("getblk: paging or unknown operation for incore busy buffer - %x\n", operation);
				/*NOTREACHED*/
				break;
			}		
		} else {
			int clear_bdone;

			/*
			 * buffer in core and not busy
			 */
			SET(bp->b_lflags, BL_BUSY);
			SET(bp->b_flags, B_CACHE);
			buf_busycount++;

			bremfree_locked(bp);
			bufstats.bufs_incore++;
			
			lck_mtx_unlock(buf_mtxp);
#ifdef JOE_DEBUG
			bp->b_owner = current_thread();
			bp->b_tag   = 1;
#endif
			if ( (bp->b_upl) )
			        panic("buffer has UPL, but not marked BUSY: %p", bp);

			clear_bdone = FALSE;
			if (!ret_only_valid) {
				/*
				 * If the number bytes that are valid is going
				 * to increase (even if we end up not doing a
				 * reallocation through allocbuf) we have to read
				 * the new size first.
				 *
				 * This is required in cases where we doing a read
				 * modify write of a already valid data on disk but
				 * in cases where the data on disk beyond (blkno + b_bcount)
				 * is invalid, we may end up doing extra I/O.
				 */
				if (operation == BLK_META && bp->b_bcount < size) {
					/*
					 * Since we are going to read in the whole size first
					 * we first have to ensure that any pending delayed write
					 * is flushed to disk first.
					 */
					if (ISSET(bp->b_flags, B_DELWRI)) {
						CLR(bp->b_flags, B_CACHE);
						buf_bwrite(bp);
						goto start;
					}
					/*
					 * clear B_DONE before returning from
					 * this function so that the caller can
					 * can issue a read for the new size.
					 */
					clear_bdone = TRUE;
				}

				if (bp->b_bufsize != size)
					allocbuf(bp, size);
			}

			upl_flags = 0;
			switch (operation) {
			case BLK_WRITE:
				/*
				 * "write" operation:  let the UPL subsystem
				 * know that we intend to modify the buffer
				 * cache pages we're gathering.
				 */
				upl_flags |= UPL_WILL_MODIFY;
			case BLK_READ:
				upl_flags |= UPL_PRECIOUS;
			        if (UBCINFOEXISTS(bp->b_vp) && bp->b_bufsize) {
					kret = ubc_create_upl_kernel(vp,
							      ubc_blktooff(vp, bp->b_lblkno), 
							      bp->b_bufsize, 
							      &upl, 
							      &pl,
							      upl_flags,
							      VM_KERN_MEMORY_FILE);
					if (kret != KERN_SUCCESS)
					        panic("Failed to create UPL");

					bp->b_upl = upl;

					if (upl_valid_page(pl, 0)) {
					        if (upl_dirty_page(pl, 0))
						        SET(bp->b_flags, B_WASDIRTY);
						else
						        CLR(bp->b_flags, B_WASDIRTY);
					} else 
					        CLR(bp->b_flags, (B_DONE | B_CACHE | B_WASDIRTY | B_DELWRI));

					kret = ubc_upl_map(upl, (vm_offset_t*)&(bp->b_datap));

					if (kret != KERN_SUCCESS)
					        panic("getblk: ubc_upl_map() failed with (%d)", kret);
				}
				break;

			case BLK_META:
				/*
				 * VM is not involved in IO for the meta data
				 * buffer already has valid data 
				 */
				break;

			default:
				panic("getblk: paging or unknown operation for incore buffer- %d\n", operation);
				/*NOTREACHED*/
				break;
			}

			if (clear_bdone)
				CLR(bp->b_flags, B_DONE);
		}
	} else { /* not incore() */
		int queue = BQ_EMPTY; /* Start with no preference */
		
		if (ret_only_valid) {
			lck_mtx_unlock(buf_mtxp);
			return (NULL);
		}
		if ((vnode_isreg(vp) == 0) || (UBCINFOEXISTS(vp) == 0) /*|| (vnode_issystem(vp) == 1)*/)
			operation = BLK_META;

		if ((bp = getnewbuf(slpflag, slptimeo, &queue)) == NULL)
			goto start;

		/*
		 * getnewbuf may block for a number of different reasons...
		 * if it does, it's then possible for someone else to
		 * create a buffer for the same block and insert it into
		 * the hash... if we see it incore at this point we dump
		 * the buffer we were working on and start over
		 */
		if (incore_locked(vp, blkno, dp)) {
			SET(bp->b_flags, B_INVAL);
			binshash(bp, &invalhash);

			lck_mtx_unlock(buf_mtxp);

			buf_brelse(bp);
			goto start;
		}
		/*
		 * NOTE: YOU CAN NOT BLOCK UNTIL binshash() HAS BEEN
		 *       CALLED!  BE CAREFUL.
		 */

		/*
		 * mark the buffer as B_META if indicated
		 * so that when buffer is released it will goto META queue
		 */
		if (operation == BLK_META)
		        SET(bp->b_flags, B_META);

		bp->b_blkno = bp->b_lblkno = blkno;
		bp->b_vp = vp;

		/*
		 * Insert in the hash so that incore() can find it 
		 */
		binshash(bp, BUFHASH(vp, blkno)); 

		bgetvp_locked(vp, bp);

		lck_mtx_unlock(buf_mtxp);

		allocbuf(bp, size);

		upl_flags = 0;
		switch (operation) {
		case BLK_META:
			/*
			 * buffer data is invalid...
			 *
			 * I don't want to have to retake buf_mtxp,
			 * so the miss and vmhits counters are done
			 * with Atomic updates... all other counters
			 * in bufstats are protected with either
			 * buf_mtxp or iobuffer_mtxp
			 */
		        OSAddAtomicLong(1, &bufstats.bufs_miss);
			break;

		case BLK_WRITE:
			/*
			 * "write" operation:  let the UPL subsystem know
			 * that we intend to modify the buffer cache pages
			 * we're gathering.
			 */
			upl_flags |= UPL_WILL_MODIFY;
		case BLK_READ:
		  {     off_t	f_offset;
			size_t 	contig_bytes;
			int	bmap_flags;

#if DEVELOPMENT || DEBUG
			/*
			 * Apple implemented file systems use UBC excludively; they should
			 * not call in here."
			 */
			const char* excldfs[] = {"hfs", "afpfs", "smbfs", "acfs",
						 "exfat", "msdos", "webdav", NULL};

			for (int i = 0; excldfs[i] != NULL; i++) {
				if (vp->v_mount &&
				    !strcmp(vp->v_mount->mnt_vfsstat.f_fstypename,
						excldfs[i])) {
					panic("%s %s calls buf_getblk",
						excldfs[i],
						operation == BLK_READ ? "BLK_READ" : "BLK_WRITE");
				}
			}
#endif

			if ( (bp->b_upl) )
				panic("bp already has UPL: %p",bp);

			f_offset = ubc_blktooff(vp, blkno);

			upl_flags |= UPL_PRECIOUS;
			kret = ubc_create_upl_kernel(vp,
					      f_offset,
					      bp->b_bufsize, 
					      &upl,
					      &pl,
					      upl_flags,
					      VM_KERN_MEMORY_FILE);

			if (kret != KERN_SUCCESS)
				panic("Failed to create UPL");
#if  UPL_DEBUG
			upl_ubc_alias_set(upl, (uintptr_t) bp, (uintptr_t) 4);
#endif /* UPL_DEBUG */
			bp->b_upl = upl;

			if (upl_valid_page(pl, 0)) {

			        if (operation == BLK_READ)
				        bmap_flags = VNODE_READ;
				else
				        bmap_flags = VNODE_WRITE;

				SET(bp->b_flags, B_CACHE | B_DONE);

			        OSAddAtomicLong(1, &bufstats.bufs_vmhits);

				bp->b_validoff = 0;
				bp->b_dirtyoff = 0;

				if (upl_dirty_page(pl, 0)) {
					/* page is dirty */
				        SET(bp->b_flags, B_WASDIRTY);

					bp->b_validend = bp->b_bcount;
					bp->b_dirtyend = bp->b_bcount;
				} else {
					/* page is clean */
					bp->b_validend = bp->b_bcount;
					bp->b_dirtyend = 0;
				}
				/*
				 * try to recreate the physical block number associated with
				 * this buffer...
				 */
				if (VNOP_BLOCKMAP(vp, f_offset, bp->b_bcount, &bp->b_blkno, &contig_bytes, NULL, bmap_flags, NULL))
				        panic("getblk: VNOP_BLOCKMAP failed");
				/*
				 * if the extent represented by this buffer
				 * is not completely physically contiguous on
				 * disk, than we can't cache the physical mapping
				 * in the buffer header
				 */
				if ((long)contig_bytes < bp->b_bcount)
				        bp->b_blkno = bp->b_lblkno;
			} else {
			        OSAddAtomicLong(1, &bufstats.bufs_miss);
			}
			kret = ubc_upl_map(upl, (vm_offset_t *)&(bp->b_datap));

			if (kret != KERN_SUCCESS)
			        panic("getblk: ubc_upl_map() failed with (%d)", kret);
			break;
		  } // end BLK_READ
		default:
			panic("getblk: paging or unknown operation - %x", operation);
			/*NOTREACHED*/
			break;
		} // end switch
	} //end buf_t !incore

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 386)) | DBG_FUNC_END,
		     bp, bp->b_datap, bp->b_flags, 3, 0);

#ifdef JOE_DEBUG
	(void) OSBacktrace(&bp->b_stackgetblk[0], 6);
#endif
	return (bp);
}