#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  size_t off_t ;
typedef  int daddr64_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  TYPE_2__* buf_t ;
struct TYPE_17__ {int b_blkno; int b_lblkno; int b_bcount; int b_flags; size_t b_bufsize; size_t b_resid; scalar_t__ b_datap; } ;
struct TYPE_16__ {int /*<<< orphan*/  v_numoutput; } ;

/* Variables and functions */
 int B_READ ; 
 int /*<<< orphan*/  ISSET (int,int) ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int VNODE_READ ; 
 int VNODE_WRITE ; 
 int VNOP_BLOCKMAP (TYPE_1__*,size_t,int,int*,size_t*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int VNOP_STRATEGY (TYPE_2__*) ; 
 TYPE_2__* alloc_io_buf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_biodone (TYPE_2__*) ; 
 scalar_t__ buf_biowait (TYPE_2__*) ; 
 int /*<<< orphan*/  buf_free (TYPE_2__*) ; 
 int /*<<< orphan*/  buf_reset (TYPE_2__*,int) ; 
 int /*<<< orphan*/  buf_seterror (TYPE_2__*,int) ; 
 TYPE_1__* buf_vnode (TYPE_2__*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
buf_strategy_fragmented(vnode_t devvp, buf_t bp, off_t f_offset, size_t contig_bytes)
{
	vnode_t	vp = buf_vnode(bp);
	buf_t	io_bp;			 /* For reading or writing a single block */
	int	io_direction;
	int	io_resid;
	size_t	io_contig_bytes;
        daddr64_t io_blkno;
	int	error = 0;
	int	bmap_flags;

	/*
	 * save our starting point... the bp was already mapped
	 * in buf_strategy before we got called
	 * no sense doing it again.
	 */
	io_blkno = bp->b_blkno;
	/*
	 * Make sure we redo this mapping for the next I/O
	 * i.e. this can never be a 'permanent' mapping
	 */
	bp->b_blkno = bp->b_lblkno;
	
	/*
	 * Get an io buffer to do the deblocking
	 */
	io_bp = alloc_io_buf(devvp, 0);

	io_bp->b_lblkno = bp->b_lblkno;
	io_bp->b_datap  = bp->b_datap;
	io_resid	= bp->b_bcount;
        io_direction	= bp->b_flags & B_READ;
	io_contig_bytes = contig_bytes;
	
	if (bp->b_flags & B_READ)
	        bmap_flags = VNODE_READ;
	else
	        bmap_flags = VNODE_WRITE;

	for (;;) {
		if (io_blkno == -1)
		        /*
			 * this is unexepected, but we'll allow for it
			 */
		        bzero((caddr_t)io_bp->b_datap, (int)io_contig_bytes);
		else {
		        io_bp->b_bcount	 = io_contig_bytes;
			io_bp->b_bufsize = io_contig_bytes;
			io_bp->b_resid   = io_contig_bytes;
			io_bp->b_blkno   = io_blkno;

			buf_reset(io_bp, io_direction);

			/*
			 * Call the device to do the I/O and wait for it.  Make sure the appropriate party is charged for write
			 */

			if (!ISSET(bp->b_flags, B_READ))
			        OSAddAtomic(1, &devvp->v_numoutput);

			if ((error = VNOP_STRATEGY(io_bp)))
			        break;
			if ((error = (int)buf_biowait(io_bp)))
			        break;
			if (io_bp->b_resid) {
			        io_resid -= (io_contig_bytes - io_bp->b_resid);
				break;
			}
		}
		if ((io_resid -= io_contig_bytes) == 0)
		        break;
		f_offset       += io_contig_bytes;
		io_bp->b_datap += io_contig_bytes;

		/*
		 * Map the current position to a physical block number
		 */
		if ((error = VNOP_BLOCKMAP(vp, f_offset, io_resid, &io_blkno, &io_contig_bytes, NULL, bmap_flags, NULL)))
		        break;
	}
	buf_free(io_bp);
	
	if (error)
	        buf_seterror(bp, error);
	bp->b_resid = io_resid;
	/*
	 * This I/O is now complete
	 */
	buf_biodone(bp);

	return error;
}