#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
struct vnop_write_args {int a_ioflag; struct uio* a_uio; struct vnode* a_vp; } ;
struct TYPE_5__ {TYPE_1__* vu_specinfo; } ;
struct vnode {int v_type; int v_specsize; int v_specdevsize; int /*<<< orphan*/  v_rdev; TYPE_2__ v_un; } ;
struct uio {scalar_t__ uio_rw; int uio_offset; int /*<<< orphan*/  uio_segflg; } ;
struct buf {int dummy; } ;
struct _throttle_io_info_t {int /*<<< orphan*/  throttle_last_write_timestamp; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  daddr64_t ;
struct TYPE_6__ {int (* d_write ) (int /*<<< orphan*/ ,struct uio*,int) ;int /*<<< orphan*/  d_type; } ;
struct TYPE_4__ {size_t si_devbsdunit; int /*<<< orphan*/  si_isssd; int /*<<< orphan*/  si_throttleable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_WRITE ; 
 int /*<<< orphan*/  D_DISK ; 
 int EINVAL ; 
 int IO_SYNC ; 
 int /*<<< orphan*/  NOCRED ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UIO_SEG_IS_USER_SPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ UIO_WRITE ; 
#define  VBLK 129 
#define  VCHR 128 
 struct _throttle_io_info_t* _throttle_io_info ; 
 int buf_bawrite (struct buf*) ; 
 int buf_bdwrite (struct buf*) ; 
 scalar_t__ buf_bread (struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  buf_brelse (struct buf*) ; 
 int buf_bwrite (struct buf*) ; 
 scalar_t__ buf_dataptr (struct buf*) ; 
 scalar_t__ buf_error (struct buf*) ; 
 struct buf* buf_getblk (struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_markaged (struct buf*) ; 
 int /*<<< orphan*/  buf_resid (struct buf*) ; 
 TYPE_3__* cdevsw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int stub1 (int /*<<< orphan*/ ,struct uio*,int) ; 
 int /*<<< orphan*/  throttle_info_end_io_internal (struct _throttle_io_info_t*,int) ; 
 int throttle_info_update_internal (struct _throttle_io_info_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_resid (struct uio*) ; 
 int uiomove (char*,int,struct uio*) ; 

int
spec_write(struct vnop_write_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
	struct buf *bp;
	daddr64_t bn;
	int bsize, blkmask, bscale;
	int io_sync;
	int devBlockSize=0;
	int n, on;
	int error = 0;
	dev_t dev;

#if DIAGNOSTIC
	if (uio->uio_rw != UIO_WRITE)
		panic("spec_write mode");
	if (UIO_SEG_IS_USER_SPACE(uio->uio_segflg))
		panic("spec_write proc");
#endif

	switch (vp->v_type) {

	case VCHR:
		{
			struct _throttle_io_info_t *throttle_info = NULL;
			int thread_throttle_level;
                if (cdevsw[major(vp->v_rdev)].d_type == D_DISK && vp->v_un.vu_specinfo->si_throttleable) {
			throttle_info = &_throttle_io_info[vp->v_un.vu_specinfo->si_devbsdunit];

				thread_throttle_level = throttle_info_update_internal(throttle_info, NULL, 0, vp->v_un.vu_specinfo->si_isssd, TRUE, NULL);

			microuptime(&throttle_info->throttle_last_write_timestamp);
                }
		error = (*cdevsw[major(vp->v_rdev)].d_write)
			(vp->v_rdev, uio, ap->a_ioflag);

			if (throttle_info) {
				throttle_info_end_io_internal(throttle_info, thread_throttle_level);
			}

		return (error);
		}

	case VBLK:
		if (uio_resid(uio) == 0)
			return (0);
		if (uio->uio_offset < 0)
			return (EINVAL);

		io_sync = (ap->a_ioflag & IO_SYNC);

		dev = (vp->v_rdev);

		devBlockSize = vp->v_specsize;
		if (devBlockSize > PAGE_SIZE)
			return(EINVAL);

	        bscale = PAGE_SIZE / devBlockSize;
		blkmask = bscale - 1;
		bsize = bscale * devBlockSize;
		

		do {
			bn = (daddr64_t)((uio->uio_offset / devBlockSize) &~ blkmask);
			on = uio->uio_offset % bsize;

			n = min((unsigned)(bsize - on), uio_resid(uio));

			/*
			 * Use buf_getblk() as an optimization IFF:
			 *
			 * 1)	We are reading exactly a block on a block
			 *	aligned boundary
			 * 2)	We know the size of the device from spec_open
			 * 3)	The read doesn't span the end of the device
			 *
			 * Otherwise, we fall back on buf_bread().
			 */
			if (n == bsize &&
			    vp->v_specdevsize != (u_int64_t)0 &&
			    (uio->uio_offset + (u_int64_t)n) > vp->v_specdevsize) {
			    /* reduce the size of the read to what is there */
			    n = (uio->uio_offset + (u_int64_t)n) - vp->v_specdevsize;
			}

			if (n == bsize)
			        bp = buf_getblk(vp, bn, bsize, 0, 0, BLK_WRITE);
			else
			        error = (int)buf_bread(vp, bn, bsize, NOCRED, &bp);

			/* Translate downstream error for upstream, if needed */
			if (!error)
				error = (int)buf_error(bp);
			if (error) {
				buf_brelse(bp);
				return (error);
			}
			n = min(n, bsize - buf_resid(bp));

			error = uiomove((char *)buf_dataptr(bp) + on, n, uio);
			if (error) {
				buf_brelse(bp);
				return (error);
			}
			buf_markaged(bp);

			if (io_sync) 
			        error = buf_bwrite(bp);
			else {
			        if ((n + on) == bsize)
				        error = buf_bawrite(bp);
				else
				        error = buf_bdwrite(bp);
			}
		} while (error == 0 && uio_resid(uio) > 0 && n != 0);
		return (error);

	default:
		panic("spec_write type");
	}
	/* NOTREACHED */

	return (0);
}