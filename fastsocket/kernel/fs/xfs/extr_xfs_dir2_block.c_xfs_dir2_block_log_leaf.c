#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * t_mountp; } ;
typedef  TYPE_1__ xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_t ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ xfs_dabuf_t ;
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_da_log_buf (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_dir2_block_leaf_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_dir2_block_log_leaf(
	xfs_trans_t		*tp,		/* transaction structure */
	xfs_dabuf_t		*bp,		/* block buffer */
	int			first,		/* index of first logged leaf */
	int			last)		/* index of last logged leaf */
{
	xfs_dir2_block_t	*block;		/* directory block structure */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_mount_t		*mp;		/* filesystem mount point */

	mp = tp->t_mountp;
	block = bp->data;
	btp = xfs_dir2_block_tail_p(mp, block);
	blp = xfs_dir2_block_leaf_p(btp);
	xfs_da_log_buf(tp, bp, (uint)((char *)&blp[first] - (char *)block),
		(uint)((char *)&blp[last + 1] - (char *)block - 1));
}