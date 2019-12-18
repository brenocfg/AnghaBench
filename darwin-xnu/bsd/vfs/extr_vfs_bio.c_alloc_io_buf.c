#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct bufattr {int dummy; } ;
typedef  TYPE_2__* mount_t ;
typedef  TYPE_3__* buf_t ;
struct TYPE_15__ {scalar_t__ bufs_iobufinuse_vdev; scalar_t__ bufs_iobufinuse; scalar_t__ bufs_iobufmax; int /*<<< orphan*/  bufs_iobufsleeps; } ;
struct TYPE_14__ {TYPE_3__* tqh_first; } ;
struct TYPE_13__ {int b_lflags; int b_tag; int /*<<< orphan*/  b_dev; int /*<<< orphan*/  b_attr; TYPE_1__* b_vp; void* b_fsprivate; int /*<<< orphan*/ * b_upl; scalar_t__ b_bufsize; scalar_t__ b_bcount; scalar_t__ b_resid; scalar_t__ b_error; int /*<<< orphan*/ * b_iodone; int /*<<< orphan*/  b_owner; scalar_t__ b_lblkno; scalar_t__ b_blkno; scalar_t__ b_redundancy_flags; scalar_t__ b_flags; scalar_t__ b_datap; int /*<<< orphan*/ * b_proc; scalar_t__ b_timestamp; } ;
struct TYPE_12__ {int mnt_kern_flag; scalar_t__ mnt_iobufinuse; } ;
struct TYPE_11__ {scalar_t__ v_type; int /*<<< orphan*/  v_rdev; TYPE_2__* v_mount; } ;

/* Variables and functions */
 int BL_BUSY ; 
 int BL_IOBUF ; 
 int BL_IOBUF_VDEV ; 
 int FALSE ; 
 int MNTK_VIRTUALDEV ; 
 scalar_t__ MNT_VIRTUALDEV_MAX_IOBUFS ; 
 int /*<<< orphan*/  NODEV ; 
 scalar_t__ NRESERVEDIOBUFS ; 
 int PRIBIO ; 
 int PSPIN ; 
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 scalar_t__ VIRTUALDEV_MAX_IOBUFS ; 
 int /*<<< orphan*/  b_freelist ; 
 TYPE_6__ bufstats ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_2__* dead_mountp ; 
 int /*<<< orphan*/  iobuffer_mtxp ; 
 TYPE_4__ iobufqueue ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *) ; 
 int need_iobuffer ; 
 scalar_t__ niobuf_headers ; 

buf_t
alloc_io_buf(vnode_t vp, int priv)
{
	buf_t	bp;
	mount_t mp = NULL;
	int alloc_for_virtualdev = FALSE;

	lck_mtx_lock_spin(iobuffer_mtxp);

	/*
	 * We subject iobuf requests for diskimages to additional restrictions.
	 *
	 * a) A single diskimage mount cannot use up more than
	 * MNT_VIRTUALDEV_MAX_IOBUFS. However,vm privileged (pageout) requests
	 * are not subject to this restriction.
	 * b) iobuf headers used by all diskimage headers by all mount
	 * points cannot exceed  VIRTUALDEV_MAX_IOBUFS.
	 */
	if (vp && ((mp = vp->v_mount)) && mp != dead_mountp &&
	    mp->mnt_kern_flag & MNTK_VIRTUALDEV) {
		alloc_for_virtualdev = TRUE;
		while ((!priv && mp->mnt_iobufinuse > MNT_VIRTUALDEV_MAX_IOBUFS) ||
		    bufstats.bufs_iobufinuse_vdev > VIRTUALDEV_MAX_IOBUFS) {
			bufstats.bufs_iobufsleeps++;

			need_iobuffer = 1;
			(void)msleep(&need_iobuffer, iobuffer_mtxp,
			    PSPIN | (PRIBIO+1), (const char *)"alloc_io_buf (1)",
			    NULL);
		}
	}

	while (((niobuf_headers - NRESERVEDIOBUFS < bufstats.bufs_iobufinuse) && !priv) || 
	       (bp = iobufqueue.tqh_first) == NULL) {
		bufstats.bufs_iobufsleeps++;

		need_iobuffer = 1;
		(void)msleep(&need_iobuffer, iobuffer_mtxp, PSPIN | (PRIBIO+1),
		    (const char *)"alloc_io_buf (2)", NULL);
	}
	TAILQ_REMOVE(&iobufqueue, bp, b_freelist);

	bufstats.bufs_iobufinuse++;
	if (bufstats.bufs_iobufinuse > bufstats.bufs_iobufmax)
		bufstats.bufs_iobufmax = bufstats.bufs_iobufinuse;

	if (alloc_for_virtualdev) {
		mp->mnt_iobufinuse++;
		bufstats.bufs_iobufinuse_vdev++;
	}

	lck_mtx_unlock(iobuffer_mtxp);

	/*
	 * initialize various fields
	 * we don't need to hold the mutex since the buffer
	 * is now private... the vp should have a reference 
	 * on it and is not protected by this mutex in any event
	 */
	bp->b_timestamp = 0; 
	bp->b_proc = NULL;

	bp->b_datap = 0;
	bp->b_flags = 0;
	bp->b_lflags = BL_BUSY | BL_IOBUF;
	if (alloc_for_virtualdev)
		bp->b_lflags |= BL_IOBUF_VDEV;
	bp->b_redundancy_flags = 0;
	bp->b_blkno = bp->b_lblkno = 0;
#ifdef JOE_DEBUG
	bp->b_owner = current_thread();
	bp->b_tag   = 6;
#endif
	bp->b_iodone = NULL;
	bp->b_error = 0;
	bp->b_resid = 0;
	bp->b_bcount = 0;
	bp->b_bufsize = 0;
	bp->b_upl = NULL;
	bp->b_fsprivate = (void *)NULL;
	bp->b_vp = vp;
	bzero(&bp->b_attr, sizeof(struct bufattr));

	if (vp && (vp->v_type == VBLK || vp->v_type == VCHR))
		bp->b_dev = vp->v_rdev;
	else
		bp->b_dev = NODEV;

	return (bp);
}