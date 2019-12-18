#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * m_sb_bp; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int XBF_TRYLOCK ; 
 int /*<<< orphan*/  XFS_BUF_CPSEMA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_BUF_HOLD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_BUF_ISDONE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_BUF_PSEMA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

xfs_buf_t *
xfs_getsb(
	xfs_mount_t	*mp,
	int		flags)
{
	xfs_buf_t	*bp;

	ASSERT(mp->m_sb_bp != NULL);
	bp = mp->m_sb_bp;
	if (flags & XBF_TRYLOCK) {
		if (!XFS_BUF_CPSEMA(bp)) {
			return NULL;
		}
	} else {
		XFS_BUF_PSEMA(bp, PRIBIO);
	}
	XFS_BUF_HOLD(bp);
	ASSERT(XFS_BUF_ISDONE(bp));
	return bp;
}