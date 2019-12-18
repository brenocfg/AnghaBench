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
typedef  int /*<<< orphan*/  xfs_daddr_t ;
struct xfs_buf {int dummy; } ;
typedef  struct xfs_buf xfs_buf_t ;
struct xfs_mount {int dummy; } ;
struct xfs_buftarg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BUF_BUSY (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_BUF_READ (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_BUF_SET_ADDR (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 struct xfs_buf* xfs_buf_get_uncached (struct xfs_buftarg*,size_t,int) ; 
 int xfs_buf_iowait (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_lock (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfsbdstrat (struct xfs_mount*,struct xfs_buf*) ; 

struct xfs_buf *
xfs_buf_read_uncached(
	struct xfs_mount	*mp,
	struct xfs_buftarg	*target,
	xfs_daddr_t		daddr,
	size_t			length,
	int			flags)
{
	xfs_buf_t		*bp;
	int			error;

	bp = xfs_buf_get_uncached(target, length, flags);
	if (!bp)
		return NULL;

	/* set up the buffer for a read IO */
	xfs_buf_lock(bp);
	XFS_BUF_SET_ADDR(bp, daddr);
	XFS_BUF_READ(bp);
	XFS_BUF_BUSY(bp);

	xfsbdstrat(mp, bp);
	error = xfs_buf_iowait(bp);
	if (error) {
		xfs_buf_relse(bp);
		return NULL;
	}
	return bp;
}