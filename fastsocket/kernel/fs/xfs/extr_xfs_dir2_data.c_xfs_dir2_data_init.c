#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_22__ {int m_dirblksize; } ;
typedef  TYPE_4__ xfs_mount_t ;
struct TYPE_23__ {TYPE_4__* i_mount; } ;
typedef  TYPE_5__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_db_t ;
struct TYPE_24__ {void* length; void* freetag; } ;
typedef  TYPE_6__ xfs_dir2_data_unused_t ;
struct TYPE_21__ {TYPE_2__* bestfree; int /*<<< orphan*/  magic; } ;
struct TYPE_25__ {TYPE_3__ hdr; TYPE_1__* u; } ;
typedef  TYPE_7__ xfs_dir2_data_t ;
struct TYPE_26__ {TYPE_7__* data; } ;
typedef  TYPE_8__ xfs_dabuf_t ;
struct TYPE_27__ {int /*<<< orphan*/ * trans; TYPE_5__* dp; } ;
typedef  TYPE_9__ xfs_da_args_t ;
typedef  int uint ;
struct TYPE_20__ {void* length; void* offset; } ;
struct TYPE_19__ {TYPE_6__ unused; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DIR2_DATA_FD_COUNT ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int xfs_da_get_buf (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_8__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_unused (int /*<<< orphan*/ *,TYPE_8__*,TYPE_6__*) ; 
 void** xfs_dir2_data_unused_tag_p (TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_4__*,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_data_init(
	xfs_da_args_t		*args,		/* directory operation args */
	xfs_dir2_db_t		blkno,		/* logical dir block number */
	xfs_dabuf_t		**bpp)		/* output block buffer */
{
	xfs_dabuf_t		*bp;		/* block buffer */
	xfs_dir2_data_t		*d;		/* pointer to block */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_data_unused_t	*dup;		/* unused entry pointer */
	int			error;		/* error return value */
	int			i;		/* bestfree index */
	xfs_mount_t		*mp;		/* filesystem mount point */
	xfs_trans_t		*tp;		/* transaction pointer */
	int                     t;              /* temp */

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	/*
	 * Get the buffer set up for the block.
	 */
	error = xfs_da_get_buf(tp, dp, xfs_dir2_db_to_da(mp, blkno), -1, &bp,
		XFS_DATA_FORK);
	if (error) {
		return error;
	}
	ASSERT(bp != NULL);
	/*
	 * Initialize the header.
	 */
	d = bp->data;
	d->hdr.magic = cpu_to_be32(XFS_DIR2_DATA_MAGIC);
	d->hdr.bestfree[0].offset = cpu_to_be16(sizeof(d->hdr));
	for (i = 1; i < XFS_DIR2_DATA_FD_COUNT; i++) {
		d->hdr.bestfree[i].length = 0;
		d->hdr.bestfree[i].offset = 0;
	}
	/*
	 * Set up an unused entry for the block's body.
	 */
	dup = &d->u[0].unused;
	dup->freetag = cpu_to_be16(XFS_DIR2_DATA_FREE_TAG);

	t=mp->m_dirblksize - (uint)sizeof(d->hdr);
	d->hdr.bestfree[0].length = cpu_to_be16(t);
	dup->length = cpu_to_be16(t);
	*xfs_dir2_data_unused_tag_p(dup) = cpu_to_be16((char *)dup - (char *)d);
	/*
	 * Log it and return it.
	 */
	xfs_dir2_data_log_header(tp, bp);
	xfs_dir2_data_log_unused(tp, bp, dup);
	*bpp = bp;
	return 0;
}