#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xfs_mount {int dummy; } ;
struct xfs_buf {int b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_META_IO_ERROR ; 
 int XBF_ASYNC ; 
 int XBF_READ ; 
 int XBF_WRITE ; 
 int /*<<< orphan*/  xfs_bdstrat_cb (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_delwri_dequeue (struct xfs_buf*) ; 
 int xfs_buf_iowait (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_force_shutdown (struct xfs_mount*,int /*<<< orphan*/ ) ; 

int
xfs_bwrite(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp)
{
	int			error;

	bp->b_flags |= XBF_WRITE;
	bp->b_flags &= ~(XBF_ASYNC | XBF_READ);

	xfs_buf_delwri_dequeue(bp);
	xfs_bdstrat_cb(bp);

	error = xfs_buf_iowait(bp);
	if (error)
		xfs_force_shutdown(mp, SHUTDOWN_META_IO_ERROR);
	xfs_buf_relse(bp);
	return error;
}